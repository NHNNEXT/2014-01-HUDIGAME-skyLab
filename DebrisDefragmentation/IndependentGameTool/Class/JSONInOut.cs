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
        private void ShowJsonData(TreeView treeView)
        {
            treeView.Nodes.Clear();
            treeView.Nodes.Add("JSONConfig");

            BuildJsonDataTree(treeView.Nodes[0], m_JsonCollection);
        }

        private void BuildJsonDataTree(TreeNode treeNode, JsonObjectCollection jObj)
        {
            foreach (var token in jObj)
            {
                if ( token.GetType() == typeof( JsonObjectCollection ))
                {
                    TreeNode node = new TreeNode(token.Name + JSON_SPLIT_TOKEN);
                    treeNode.Nodes.Add(node);

                    BuildJsonDataTree(node, (JsonObjectCollection)token);
                }
                else if ( token.GetType() == typeof( JsonArrayCollection ))
                {
                    TreeNode node = new TreeNode(token.Name + JSON_SPLIT_TOKEN);
                    treeNode.Nodes.Add(node);
                    // 배열 내의 각각의 숫자들을 다 자식으로 집어넣는다
                    foreach (var num in (JsonArrayCollection)token )
                    {
                        node.Nodes.Add(num.ToString());
                    }
                }
                else
                {
                    TreeNode node = new TreeNode(token.Name + JSON_SPLIT_TOKEN + token.GetValue().ToString());
                    treeNode.Nodes.Add(node);
                }
            }
        }

        // JSON 데이터 가져오는 곳 // 응? 이럴 필요 없는데????
        public uint GetUintVariable(JSONEnvironment.JsonKeyValues variable)
        {
            switch(variable)
            {
                case JSONEnvironment.JsonKeyValues.JSON_DEBRIS_NUMBER:
                    return Convert.ToUInt32(m_JsonCollection[JSONEnvironment.GetJsonKey(JSONEnvironment.JsonKeyValues.JSON_DEBRIS_NUMBER)].GetValue());
                default:
                    return 0;
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
                    StreamWriter sw = new StreamWriter(JSONNameToSave.Text + ".json");

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
        // JSONKeyLabel의 Text를 Key값으로 가져오고 해당하는 Value를 Json 데이터에서 지우고 새로 삽입(변경)
        // 이때 삽입되는 값은 JSONVarBar에 있는 값. 변경된 값을 최종적으로 Variable List에 출력해준다
        public void JSONModifyBtn(Label JSONKeyLabel, TextBox JSONVarBar, TreeView VariableList)
        {
            string key = JSONKeyLabel.Text;

            if (JSONVarBar.Text.Length > 0)
            {
                JsonObject job = m_JsonCollection[key];

                switch (job.GetValue().GetType().Name)
                {
                    case "String":
                        break;
                    case "Double":
                        m_JsonCollection.Remove(job);
                        m_JsonCollection.Add(new JsonNumericValue(key, Convert.ToUInt32(JSONVarBar.Text)));
                        break;
                    case "Boolean":
                        break;
                    default:
                        break;
                }
            }

            ShowJsonData(VariableList);
        }

    }
}
