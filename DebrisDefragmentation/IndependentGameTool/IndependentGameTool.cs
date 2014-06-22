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
            m_JsonManager.SearchJsonFiles(this.JsonFileList);
            SearchMesh();
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
                m_Renderer.ZoomInOutCameraPosition(-1);
            }
            else
            {
                m_Renderer.ZoomInOutCameraPosition(1);
            }
        }

        private void ObjViewMouseLeave(object sender, EventArgs e)
        {
            this.Focus();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // TAB : JSON CONFIG
        ////////////////////////////////////////////////////////////////////////////////////////////////////

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

        // tab_JSONConfig 에서 수정할 때
        private void JsonModifyDataBtn(object sender, EventArgs e)
        {
            UpdateJSONTreesAll();
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


        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // TAB : Object Tool
        ////////////////////////////////////////////////////////////////////////////////////////////////////


        private void LoadDataFromTree(object sender, EventArgs e)
        {
            SelectedObjJson.Nodes.Clear();

            if (ModelNameTxt.Text.Length == 0)
            {
                m_JsonManager.ShowJsonData(SelectedObjJson);
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
            SearchMesh();
        }

        private void SearchMesh()
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
                LoadedObjectList.Items.Add(filename);
            }
            else
            {
                System.Windows.Forms.MessageBox.Show("Select Mesh First");
            }
        }

        private void ModifyObjValue(object sender, EventArgs e)
        {
            UpdateJSONTreesAll();
        }

        private void UpdateJSONTreesAll()
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
                m_JsonManager.ShowJsonData(JsonVariables);
            }

            tn = JsonVariables.SelectedNode;
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
                m_JsonManager.ShowJsonData(SelectedObjJson);
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

        private void GetBoxDataBtn(object sender, EventArgs e)
        {
            TreeNode tn = SelectedObjJson.SelectedNode;

            if (null == tn || null == tn.Parent)
            {
                return;
            }

            if (LoadedObjectList.SelectedIndex == -1)
            {
                MessageBox.Show("Select Object First");
                return;
            }

            if (tn.Parent.Text == "AxisLength : ")
            {
                TreeNodeCollection tnc = tn.Nodes;
                ALXtxt.Text = tnc[0].Text;
                BBX.Text = tnc[0].Text;
                ALYtxt.Text = tnc[1].Text;
                BBY.Text = tnc[1].Text;
                ALZtxt.Text = tnc[2].Text;
                BBZ.Text = tnc[2].Text;

                centerPosX.Text = "0 으로 고정됩니다";
                centerPosY.Text = "0 으로 고정됩니다";
                centerPosZ.Text = "0 으로 고정됩니다";

                float lengthX = Convert.ToSingle(ALXtxt.Text);
                float lengthY = Convert.ToSingle(ALYtxt.Text);
                float lengthZ = Convert.ToSingle(ALZtxt.Text);

                m_Renderer.SetCollisionBox(LoadedObjectList.SelectedIndex,
                    lengthX, lengthY, lengthZ);
            }
        }

        private void GetScaleBtnClicked(object sender, EventArgs e)
        {
            int objIndex = LoadedObjectList.SelectedIndex;
            TreeNode tn = SelectedObjJson.SelectedNode;

            if (objIndex == -1 || tn == null)
            {
                return;
            }

            if (m_JsonManager.SplitJSONKeyFromKeyValue(tn.Text) != "Scale")
            {
                return;
            }

            scaleBox.Text = m_JsonManager.SplitJSONValueFromKeyValue(tn.Text);
            ScaleSlider.Value = Convert.ToInt16(scaleBox.Text);
        }

        private void InputScaleByUser(object sender, KeyPressEventArgs e)
        {
            if (char.IsDigit(e.KeyChar)
                || e.KeyChar == Convert.ToChar(Keys.Back)
                || e.KeyChar == Convert.ToChar("."))
            {

            }
            else // 여기 들어오면 입력 ㄴㄴ
            {
                e.Handled = true;
            }
        }

        private void SyncScaleValue(object sender, KeyEventArgs e)
        {
            string name = sender.GetType().ToString();
            SyncEachOther(name);
        }

        private void ScaleSliderScroll(object sender, EventArgs e)
        {
            string name = sender.GetType().ToString();
            SyncEachOther(name);
        }

        private void SyncEachOther(string senderName)
        {
            if (senderName.Equals("System.Windows.Forms.TextBox"))
            {
                float value = 0;
                if (scaleBox.Text.Length != 0)
                {
                    try
                    {
                        value = Convert.ToSingle(scaleBox.Text);
                    }
                    catch
                    {
                        value = 0;
                    }
                    value = (value > 20 ? 20 : value);
                    ScaleSlider.Value = Convert.ToInt16(value);
                    scaleBox.Text = value.ToString();
                }
            }
            else if (senderName.Equals("System.Windows.Forms.TrackBar"))
            {
                scaleBox.Text = ScaleSlider.Value.ToString();
            }
        }

        private void ApplyScaleBtnClicked(object sender, EventArgs e)
        {
            if (scaleBox.Text.Length == 0)
            {
                return;
            }

            float scale = Convert.ToSingle(scaleBox.Text);
            int objIdx = LoadedObjectList.SelectedIndex;

            if (objIdx == -1)
            {
                return;
            }

            m_Renderer.SetScale(objIdx, scale);
            AccumScale.Text = (Convert.ToSingle(AccumScale.Text) * scale).ToString();
        }

        private void WirdFrameOnOffBtnClicked(object sender, EventArgs e)
        {
            m_Renderer.ChangeRenderState();
        }
        // 조심해!! 본래 각각의 객체 별로 Scale을 별도 저장하고 있어야 해!
        private void ResetAccumulatedScale(object sender, EventArgs e)
        {
            AccumScale.Text = "1.0";
        }

    }
}
