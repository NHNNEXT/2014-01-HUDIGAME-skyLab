#pragma once

template<typename TElem, int QSize>
class ProducerConsumerQueue
{
public:
	ProducerConsumerQueue() : mOccupiedSize( 0 ), mQueueOffset( 0 )
	{
		memset( mQueueArray, 0, sizeof( mQueueArray ) );
		InitializeConditionVariable( &mNotFull );
		InitializeConditionVariable( &mNotEmpty );
		InitializeSRWLock( &mSRWLock );
	}

	~ProducerConsumerQueue() {}

	// 큐에 집어 넣는다
	bool Produce( const TElem& item, bool waitUntilConsume = true )
	{
		// 쓰기니까 exclusive
		AcquireSRWLockExclusive( &mSRWLock );

		while ( mOccupiedSize == QSize )
		{
			// 가득 차 있는 경우
			if ( waitUntilConsume )
			{
				/// 큐에 넣을 공간 생길때까지 잔다.
				// mNotFull이 true가 될 때까지 락을 풀어 놓음 - 꺼내갈 수 있게
				SleepConditionVariableSRW( &mNotFull, &mSRWLock, INFINITE, 0 );
			}
			else
			{
				// 락을 풀고, 못 넣었다! 리턴
				ReleaseSRWLockExclusive( &mSRWLock );
				return false;
			}
		}

		// 지금 차 있는 데이터 시작 점 + 지금 차 있는 데이터 크기 = 지금 쓸 자리
		mQueueArray[( mQueueOffset + mOccupiedSize ) % QSize] = item;
		++mOccupiedSize;

		ReleaseSRWLockExclusive( &mSRWLock );

		// 채워놨다!
		WakeConditionVariable( &mNotEmpty );

		return true;
	}

	// 큐에서 뺀다
	bool Consume( TElem& item, bool waitUntilProduce = true )
	{
		// 뺄 때도 변경이 생기므로 exclusive
		AcquireSRWLockExclusive( &mSRWLock );

		while ( mOccupiedSize == 0 )
		{
			if ( waitUntilProduce )
			{
				/// 큐에 아이템 들어올때까지 잔다
				// mNotEmpty가 true가 될 때까지 락을 풀어 놓음 - 채울 수 있게
				SleepConditionVariableSRW( &mNotEmpty, &mSRWLock, INFINITE, 0 );
			}
			else
			{
				ReleaseSRWLockExclusive( &mSRWLock );
				return false;
			}

		}

		item = mQueueArray[mQueueOffset];
		--mOccupiedSize;

		// 시작점을 꺼내가니까 시작점을 밀기
		if ( ++mQueueOffset == QSize )
			mQueueOffset = 0;

		ReleaseSRWLockExclusive( &mSRWLock );

		// 꺼내갔다!
		WakeConditionVariable( &mNotFull );

		return true;
	}

private:
	TElem mQueueArray[QSize];

	uint32_t mOccupiedSize;
	uint32_t mQueueOffset;

	CONDITION_VARIABLE mNotFull;
	CONDITION_VARIABLE mNotEmpty;

	SRWLOCK mSRWLock;
};


