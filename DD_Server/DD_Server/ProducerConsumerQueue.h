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

	// ť�� ���� �ִ´�
	bool Produce( const TElem& item, bool waitUntilConsume = true )
	{
		// ����ϱ� exclusive
		AcquireSRWLockExclusive( &mSRWLock );

		while ( mOccupiedSize == QSize )
		{
			// ���� �� �ִ� ���
			if ( waitUntilConsume )
			{
				/// ť�� ���� ���� ���涧���� �ܴ�.
				// mNotFull�� true�� �� ������ ���� Ǯ�� ���� - ������ �� �ְ�
				SleepConditionVariableSRW( &mNotFull, &mSRWLock, INFINITE, 0 );
			}
			else
			{
				// ���� Ǯ��, �� �־���! ����
				ReleaseSRWLockExclusive( &mSRWLock );
				return false;
			}
		}

		// ���� �� �ִ� ������ ���� �� + ���� �� �ִ� ������ ũ�� = ���� �� �ڸ�
		mQueueArray[( mQueueOffset + mOccupiedSize ) % QSize] = item;
		++mOccupiedSize;

		ReleaseSRWLockExclusive( &mSRWLock );

		// ä������!
		WakeConditionVariable( &mNotEmpty );

		return true;
	}

	// ť���� ����
	bool Consume( TElem& item, bool waitUntilProduce = true )
	{
		// �� ���� ������ ����Ƿ� exclusive
		AcquireSRWLockExclusive( &mSRWLock );

		while ( mOccupiedSize == 0 )
		{
			if ( waitUntilProduce )
			{
				/// ť�� ������ ���ö����� �ܴ�
				// mNotEmpty�� true�� �� ������ ���� Ǯ�� ���� - ä�� �� �ְ�
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

		// �������� �������ϱ� �������� �б�
		if ( ++mQueueOffset == QSize )
			mQueueOffset = 0;

		ReleaseSRWLockExclusive( &mSRWLock );

		// ��������!
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


