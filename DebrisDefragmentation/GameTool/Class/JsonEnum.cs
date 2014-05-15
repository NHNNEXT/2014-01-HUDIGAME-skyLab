// C#이랑 C++에서 동시에 JSON 키 값을 사용하기 위한 파일

///# 헐.... 라인 매크로는 C#에 없으니까 이렇게 한겨?
#if !__LINE__
namespace DDWrapper {
public 

#endif

enum JsonKeyValues : int
{
	JSON_DEBRIS_NUMBER = 0,
    JSON_ISS_ONE,
	JSON_TOTAL_KEY_COUNT
};

#if !__LINE__
}
#endif