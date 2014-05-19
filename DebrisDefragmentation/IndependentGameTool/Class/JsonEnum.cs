using System.Collections.Generic;

namespace GameTool.GameEnvironment
{
    static class JSONEnvironment
    {

        public enum JsonKeyValues : int
        {
            JSON_DEBRIS_NUMBER = 0,
            JSON_ISS,
            JSON_TOTAL_KEY_COUNT
        };

        public enum JsonISSModule : int
        {
            NO_MODULE = -1,
            PART0,
            PART1,
            PART2,
            PART3,
            PART4,
            PART5,
            PART6,
            PART7,
            PART8,
            PART9,
        }

        static private Dictionary<JsonKeyValues, string> JsonKeyStringList = new Dictionary<JsonKeyValues, string>()
        {
            {JsonKeyValues.JSON_DEBRIS_NUMBER, "debrisNumber"},
            {JsonKeyValues.JSON_ISS, "ISS"}
        };

        static private Dictionary<JsonISSModule, string> JsonISSModuleList = new Dictionary<JsonISSModule, string>()
        {
            { JsonISSModule.PART0, "0" },
            { JsonISSModule.PART1, "1" },
            { JsonISSModule.PART2, "2" },
            { JsonISSModule.PART3, "3" },
            { JsonISSModule.PART4, "4" },
            { JsonISSModule.PART5, "5" },
            { JsonISSModule.PART6, "6" },
            { JsonISSModule.PART7, "7" },
            { JsonISSModule.PART8, "8" },
            { JsonISSModule.PART9, "9" },
        };

        static public string GetJsonKey(JsonKeyValues key)
        {
            return JsonKeyStringList[key];
        }

        //override
        static public string GetJsonKey(JsonISSModule key)
        {
            return JsonISSModuleList[key];
        }
    }
}