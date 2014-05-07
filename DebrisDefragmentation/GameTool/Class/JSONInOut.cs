using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Json;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;

namespace GameTool.Class
{
    public enum ENUM_JSONVAR
    {
        DEBRIS_NUMBER,
    }

    class JSONInOut
    {
        JsonObjectCollection m_JsonCollection = new JsonObjectCollection();
        const string m_jsonFilePath = @".\Resources\Json\";

        public void LoadJsonFile(ListBox JsonList, ListBox VariableList, Button StartBtn)
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

                ShowJsonData(VariableList);

                MessageBox.Show("Load Json Success!");

                // 스트림 리더를 닫는다.
                sr.Close();

                // 시작 버튼을 선택 가능하게
                StartBtn.Enabled = true;
            }
        }

        private void ShowJsonData(ListBox lb)
        {
            lb.Items.Clear();

            lb.Items.Add("debrisNumber : " + m_JsonCollection["debrisNumber"].GetValue().ToString());
        }

        // JSON 데이터 가져오는 곳
        public uint GetUintVariable(ENUM_JSONVAR variable)
        {
            switch(variable)
            {
                case ENUM_JSONVAR.DEBRIS_NUMBER:
                    return Convert.ToUInt32(m_JsonCollection["debrisNumber"].GetValue());
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

        private bool IsCorrectFileName(string fileName)
        {
            Regex rg = new Regex(@"[!@#$%^&*/\\]");
            if (rg.Matches(fileName).Count > 0)
            {
                return false;
            }
            return true;
        }

        public void JSONModifyBtn(Label JSONKeyLabel, TextBox JSONVarBar, ListBox VariableList)
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
