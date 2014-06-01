using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace GameTool
{
    public partial class IndependentGameTool : Form
    {
        Class.Renderer m_Renderer = new Class.Renderer();
        Class.JSONInOut m_JsonManager = new Class.JSONInOut();

        public IndependentGameTool()
        {
            InitializeComponent();

            this.ObjectView.MouseWheel += new System.Windows.Forms.MouseEventHandler(ObjectCameraZoomInOut);
        }

        private void ISSRenderStart(object sender, EventArgs e)
        {
            m_Renderer.CreateDevice(this.ObjectView);

            Render();
        }

        private async void Render()
        {
            // 무한 루프
            while(true)
            {
                m_Renderer.Render();
                await Task.Delay(16);
            }
        }

        private void ISSPartRenderClick(object sender, EventArgs e)
        {
            this.Activate();
            this.ObjectView.Focus();
        }

        private void ObjectCameraZoomInOut(object sender, MouseEventArgs e)
        {
            // 아래로 휠
            if ( e.Delta > 0 )
            {
                m_Renderer.ZoomInOutCameraPosition(-10);
            }
            else
            {
                m_Renderer.ZoomInOutCameraPosition(10);
            }
        }

        private void ObjViewMouseLeave(object sender, EventArgs e)
        {
            this.Focus();
        }

        private void SearchJsonFile(object sender, EventArgs e)
        {
            m_JsonManager.SearchJsonFiles(this.JsonFileList);
        }

        private void LoadJsonFile(object sender, EventArgs e)
        {
            m_JsonManager.LoadJsonFile(JsonFileList, JsonVariables, RenderStartBtn);
        }

        private void TreeViewJsonDataSelected(object sender, TreeNodeMouseClickEventArgs e)
        {
            TreeNode tn = e.Node;
            if (null != tn)
            {
                string val = m_JsonManager.SplitJSONValueFromKeyValue(tn.Text);
                string key = m_JsonManager.SplitJSONKeyFromKeyValue(tn.Text);
                JSONKeyLabel.Text = key;
                JSONVarBar.Text = val;
            }
        }

        private void JsonModifyDataBtn(object sender, EventArgs e)
        {
            TreeNode tn = JsonVariables.SelectedNode;
            if (null != tn)
            {
                // 바뀐 JSON 데이터를 반영해준다
                ChangeJsonData(tn, JSONVarBar.Text);
                // Tree에 바뀐 값을 집어넣는다.
                if (tn.Text.Contains(":")) // Key : Value 형태
                {
                    tn.Text = JSONKeyLabel.Text + " : " + JSONVarBar.Text;
                }
                else // Value 형태
                {
                    tn.Text = JSONVarBar.Text;
                }
            }
        }

        private void ChangeJsonData(TreeNode node, string val)
        {
            m_JsonManager.ChangeJsonData(node, val);
        }

        private void SaveJSONFile(object sender, EventArgs e)
        {
            // 여기서 저장하기 전에 TreeView를 JsonData로 갱신할 것!

            m_JsonManager.SaveJsonFile(JSONNameToSave);
        }

        private void LoadDataFromTree(object sender, EventArgs e)
        {
            SelectedObjJson.Nodes.Clear();

            if (ModelNameTxt.Text.Length == 0)
            {
                return;
            }

            m_JsonManager.ShowJsonData(SelectedObjJson);
            TreeNode root = SelectedObjJson.Nodes[0];
            TreeNode probe = root.FirstNode;
            while (probe != null)
            {
                probe = probe.NextNode;
                if (probe != null && probe.Name == ModelNameTxt.Text)
                {
                    probe.ExpandAll();
                    while (probe != null)
                    {
                        probe.Expand();
                        probe = probe.Parent;
                    }
                }
            }
        }

        private void SearchMeshBtn(object sender, EventArgs e)
        {
            // 우선 파일 리스트를 비우고
            MeshFIleList.Items.Clear();

            // Tool 이 실행된 폴더를 찾도록 한다
            System.IO.DirectoryInfo di = new System.IO.DirectoryInfo(@".\Resources\3DModel\");

            foreach (System.IO.FileInfo f in di.GetFiles())
            {
                // 설정파일 규약을 좀 정해야겠네요
                if (f.Extension.ToString() == ".x")
                {
                    MeshFIleList.Items.Add(f.Name);
                }
            }
        }

        private void LoadMeshBtn(object sender, EventArgs e)
        {
            if (!m_Renderer.IsDeviceReady())
            {
                System.Windows.Forms.MessageBox.Show("Render First");
                return;
            }

            if (null == MeshFIleList.SelectedItem)
            {
                return;
            }

            string filename = MeshFIleList.SelectedItem.ToString();

            if (filename.Length > 0)
            {
                m_Renderer.CreateAndAddMesh(filename);
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Select Mesh First");
            }
        }

        private void ModifyObjValue(object sender, EventArgs e)
        {
            TreeNode tn = SelectedObjJson.SelectedNode;
            if (null != tn)
            {
                // 바뀐 JSON 데이터를 반영해준다
                ChangeJsonData(tn, ObjJsonValue.Text);
                // Tree에 바뀐 값을 집어넣는다.
                if (tn.Text.Contains(":")) // Key : Value 형태
                {
                    tn.Text = ObjJsonKey.Text + " : " + ObjJsonValue.Text;
                }
                else // Value 형태
                {
                    tn.Text = ObjJsonValue.Text;
                }
            }
        }

        private void ObjJsonSelected(object sender, TreeNodeMouseClickEventArgs e)
        {
            TreeNode tn = e.Node;
            if (null != tn)
            {
                string val = m_JsonManager.SplitJSONValueFromKeyValue(tn.Text);
                string key = m_JsonManager.SplitJSONKeyFromKeyValue(tn.Text);
                ObjJsonKey.Text = key;
                ObjJsonValue.Text = val;
            }
        }
    }
}
