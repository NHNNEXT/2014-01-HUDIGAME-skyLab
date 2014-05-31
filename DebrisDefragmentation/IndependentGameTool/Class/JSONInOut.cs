using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Json;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using GameTool.GameEnvironment;

namespace GameTool.Class
{
    
    class JSONInOut
    {
        JsonObjectCollection m_JsonCollection = new JsonObjectCollection();
        const string JSON_SPLIT_TOKEN = " : ";
        const string m_jsonFilePath = @".\Resources\Json\";

        public void LoadJsonFile(ListBox JsonList, TreeView VariableList, Button StartBtn)
        {
            if (JsonList.SelectedIndices.Count > 0)
            {
                string fileName = JsonList.SelectedItem.ToString();
                StreamReader sr = new StreamReader(m_jsonFilePath + fileName);

                // 파일에서 다 읽는다
                string jsonText = sr.ReadToEnd();

                // 빈 파일이면?
                if (jsonText.Length == 0)
                {
                    // 파싱 없이 리턴
                    MessageBox.Show("Empty File!");
                    return;
                }

                // 파싱한 다음
                JsonTextParser parser = new JsonTextParser();
                JsonObject obj = parser.Parse(jsonText);

                // JSON 멤버 변수로 전달한다
                m_JsonCollection = (JsonObjectCollection)obj;

                // TreeVIew에 계층별로 집어넣는다
                ShowJsonData(VariableList);

                MessageBox.Show("Load Json Success!");

                // 스트림 리더를 닫는다.
                sr.Close();

                // 시작 버튼을 선택 가능하게
                StartBtn.Enabled = true;
            }
        }

        // TreeView에 JsonData를 구축하는 함수
        public void ShowJsonData(TreeView treeView)
        {
            treeView.Nodes.Clear();
            treeView.Nodes.Add("Root","JSONConfig");

            BuildJsonDataTree(treeView.Nodes["Root"], m_JsonCollection);
        }

        private void BuildJsonDataTree(TreeNode treeNode, JsonObjectCollection jObj)
        {
            foreach (var token in jObj)
            {
                // 1. JsonObjectCollection일 경우, 자기 밑에 자식이 더 있다.
                if ( token.GetType() == typeof( JsonObjectCollection ))
                {
                    TreeNode node = new TreeNode(token.Name + JSON_SPLIT_TOKEN);
                    node.Name = token.Name;
                    treeNode.Nodes.Add(node);
                    
                    BuildJsonDataTree(node, (JsonObjectCollection)token);
                    
                }
                // 2. JsonArrayCollection일 경우, JsonObjectCollection으로 캐스팅 ㄴㄴ해
                else if ( token.GetType() == typeof( JsonArrayCollection ))
                {
                    TreeNode node = new TreeNode(token.Name + JSON_SPLIT_TOKEN);
                    node.Name = token.Name;
                    treeNode.Nodes.Add(node);

                    // 배열 내의 각각의 숫자들을 다 자식으로 집어넣는다
                    foreach (var num in (JsonArrayCollection)token )
                    {
                        node.Nodes.Add(num.ToString());
                    }
                }
                // 3. 여기까지 왔으면 진짜 노드다!
                else
                {
                    TreeNode node = new TreeNode(token.Name + JSON_SPLIT_TOKEN + token.GetValue().ToString());
                    treeNode.Nodes.Add(node);
                    node.Name = token.Name;
                }
            }
        }

        public void SearchJsonFiles(ListBox JsonFileList)
        {
            // 우선 파일 리스트를 비우고
            JsonFileList.Items.Clear();

            // Tool 이 실행된 폴더를 찾도록 한다
            System.IO.DirectoryInfo di = new System.IO.DirectoryInfo(m_jsonFilePath);

            foreach (System.IO.FileInfo f in di.GetFiles())
            {
                // 설정파일 규약을 좀 정해야겠네요
                if (f.Extension.ToString() == ".json")
                {
                    JsonFileList.Items.Add(f.Name);
                }
            }
        }

        public void SaveJsonFile(TextBox JSONNameToSave)
        {
            // 파일명이 있어야겠죠?
            if (JSONNameToSave.Text.Length > 0)
            {
                // 파일명이 적합하다면 계속 진행
                if (IsCorrectFileName(JSONNameToSave.Text))
                {
                    StreamWriter sw = new StreamWriter(m_jsonFilePath + JSONNameToSave.Text + ".json");

                    // 파일에 쓴다
                    sw.Write(m_JsonCollection.ToString());

                    MessageBox.Show("Save Json Success!");

                    // 스트림 라이터를 닫는다
                    sw.Close();
                }
                else
                {
                    MessageBox.Show("Invalid File Name!");
                    return;
                }
            }
            else
            {
                MessageBox.Show("Empty File Name!");
                return;
            }
        }

        // 파일명이 적합한지 알아보는 함수
        private bool IsCorrectFileName(string fileName)
        {
            Regex rg = new Regex(@"[!@#$%^&*/\\]");
            if (rg.Matches(fileName).Count > 0)
            {
                return false;
            }
            return true;
        }
 
        // Key : Value 쌍에서 Value만 뽑아냄
        public string SplitJSONValueFromKeyValue(string rawText)
        {
            Regex rg = new Regex(JSON_SPLIT_TOKEN);
            if (rg.Matches(rawText).Count > 0)
            {
                string[] result = rawText.Split(':');
                return result[1].Trim();
            }
            else
            {
                return rawText;
            }
        }

        // Key : Value 쌍에서 Key만 뽑아냄
        public string SplitJSONKeyFromKeyValue(string rawText)
        {
            Regex rg = new Regex(JSON_SPLIT_TOKEN);
            if (rg.Matches(rawText).Count > 0)
            {
                string[] result = rawText.Split(':');
                return result[0].Trim();
            }
            else
            {
                return rawText;
            }
        }

        public void ChangeJsonData(TreeNode changedNode, string val)
        {
            string treePath = changedNode.FullPath;
            string[] keys = treePath.Split('\\');

            for(int i = 0; i < keys.Length; ++i)
            {
                keys[i] = SplitJSONKeyFromKeyValue(keys[i]);
            }

            // 두 가지 가능성이 있다. Key : Value 형태일때와 (Object)
            // Key(부모), Value(자식) 형태일 때 (Array)
            // keys의 최상위 노드는 JSON에 없는 key이다. (i = 1 부터 시작)

            // 최하단 노드 직전까지 JSON 파일을 전개 (i = length - 2 까지)

            JsonObjectCollection jObj = m_JsonCollection;
            // 얘는 Array 일 수도 있고 아닐 수도 있다
            JsonArrayCollection jArray = null;

            for (int i = 1; i < keys.Length - 1; ++i)
            {
                // 배열일 경우 JsonObjectCollection으로 캐스팅이 안 된다
                if (jObj[keys[i]].GetType().Name == "JsonArrayCollection" )
                {
                    jArray = (JsonArrayCollection) jObj[keys[i]];
                    break;
                }
                jObj = (JsonObjectCollection) jObj[keys[i]];
            }
            
            string key = SplitJSONKeyFromKeyValue(keys[keys.Length - 1]);

            // 바뀐 노드가 통째로 key와 같다면 array
            // 그렇지 않다면 key와 value가 섞여있다는 뜻이므로 jObj
            if (keys[keys.Length - 1] != changedNode.Text)
            {
                JsonObject oldJsonObj = jObj[key];

                // 위치를 기억하고 지운 다음
                int idx = jObj.IndexOf(oldJsonObj);
                jObj.Remove(oldJsonObj);

                // 이전 위치에 끼워넣는다
                switch (oldJsonObj.GetValue().GetType().Name)
                {
                    case "String":
                        jObj.Insert(idx, new JsonStringValue(key, Convert.ToString(val)));
                        break;
                    case "Double":
                        jObj.Insert(idx, new JsonNumericValue(key, Convert.ToUInt32(val)));
                        break;
                    case "Boolean":
                        jObj.Insert(idx, new JsonBooleanValue(key, Convert.ToBoolean(val)));
                        break;
                    default:
                        break;
                }
            }
            else // 이 경우 keys[keys.Length - 1] 는 자신의 value 이다 length -2 가 key이다.
                // 그리고 key : value 쌍이 아니므로 Array 형태로 반환된 것이다.
            {
                TreeNode probe = changedNode;

                int nthChild = -1;
                while (probe != null)
                {
                    probe = probe.PrevNode;
                    ++nthChild;
                }

                // 혹시라도 이런 게 기다리고 있다면 Err
                if (nthChild == -1)
                {
                    return;
                }
                    

                JsonArrayCollection oldArray = jArray;
                switch ( oldArray[nthChild].GetType().Name )
                {
                    case "String":
                        break;
                    case "JsonNumericValue":
                        oldArray.RemoveAt(nthChild);
                        oldArray.Insert(nthChild, new JsonNumericValue(Convert.ToDouble(val)));
                        break;
                    case "Boolean":
                        break;
                    default:
                        break;
                }
            }
        }

    }
}
