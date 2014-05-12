
namespace GameEnvironment
{
    static class JSONEnvironment {
        
    public enum JsonKeyValues : int
    {
        JSON_DEBRIS_NUMBER = 0,
        JSON_ISS_ONE,
        JSON_TOTAL_KEY_COUNT
    };

    static private string[] JsonKeyStringList
        = {
              "debrisNumber"
                                 };

    static public string GetJsonKey(JsonKeyValues key)
    {
        return JsonKeyStringList[(int)key];
    }

    }
}