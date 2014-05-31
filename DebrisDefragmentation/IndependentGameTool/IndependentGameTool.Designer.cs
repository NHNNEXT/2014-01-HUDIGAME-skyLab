namespace GameTool
{
    partial class IndependentGameTool
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.View = new System.Windows.Forms.PictureBox();
            this.CameraConfig = new System.Windows.Forms.GroupBox();
            this.CameraResetBtn = new System.Windows.Forms.Button();
            this.CameraViewVector = new System.Windows.Forms.GroupBox();
            this.CameraViewVecZ = new System.Windows.Forms.TextBox();
            this.CameraViewVecY = new System.Windows.Forms.TextBox();
            this.CameraViewVecX = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cameraZpos = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cameraYpos = new System.Windows.Forms.TextBox();
            this.cameraXpos = new System.Windows.Forms.TextBox();
            this.TimerStatus = new System.Windows.Forms.GroupBox();
            this.TimePass = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.PlayerStatusReset = new System.Windows.Forms.Button();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.IntegratedVelVal = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.PlayerVelocityZ = new System.Windows.Forms.TextBox();
            this.PlayerVelocityY = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.PlayerVelocityX = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.IntegratedAccelVal = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.PlayerAccelZ = new System.Windows.Forms.TextBox();
            this.PlayerAccelY = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.PlayerAccelX = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.PlayerPosZ = new System.Windows.Forms.TextBox();
            this.PlayerPosY = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.PlayerPosX = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.Status = new System.Windows.Forms.TabControl();
            this.JSONConfig = new System.Windows.Forms.TabPage();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.JsonVariables = new System.Windows.Forms.TreeView();
            this.JSONKeyLabel = new System.Windows.Forms.Label();
            this.MdoifyValue = new System.Windows.Forms.Button();
            this.JSONVarBar = new System.Windows.Forms.TextBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.label15 = new System.Windows.Forms.Label();
            this.JSONSaveFilebtn = new System.Windows.Forms.Button();
            this.JSONNameToSave = new System.Windows.Forms.TextBox();
            this.RenderStartBtn = new System.Windows.Forms.Button();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.JSONLoadFilebtn = new System.Windows.Forms.Button();
            this.JsonFileList = new System.Windows.Forms.ListBox();
            this.JSONSearchFilebtn = new System.Windows.Forms.Button();
            this.CameraModelStat = new System.Windows.Forms.TabPage();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.FPSshow = new System.Windows.Forms.Label();
            this.ObjectTool = new System.Windows.Forms.TabPage();
            this.ISSRenderBtn = new System.Windows.Forms.Button();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.ObjJsonKey = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.ObjJsonValue = new System.Windows.Forms.TextBox();
            this.groupBox13 = new System.Windows.Forms.GroupBox();
            this.MeshFIleList = new System.Windows.Forms.ListBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SelectedObjJson = new System.Windows.Forms.TreeView();
            this.groupBox12 = new System.Windows.Forms.GroupBox();
            this.LoadObjDataBtn = new System.Windows.Forms.Button();
            this.ModelNameTxt = new System.Windows.Forms.TextBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tab_GameRender = new System.Windows.Forms.TabPage();
            this.tab_ISSPartRender = new System.Windows.Forms.TabPage();
            this.ObjectView = new System.Windows.Forms.PictureBox();
            this.groupBox14 = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.View)).BeginInit();
            this.CameraConfig.SuspendLayout();
            this.CameraViewVector.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.TimerStatus.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.Status.SuspendLayout();
            this.JSONConfig.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.CameraModelStat.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.ObjectTool.SuspendLayout();
            this.groupBox10.SuspendLayout();
            this.groupBox13.SuspendLayout();
            this.groupBox12.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tab_GameRender.SuspendLayout();
            this.tab_ISSPartRender.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ObjectView)).BeginInit();
            this.groupBox14.SuspendLayout();
            this.SuspendLayout();
            // 
            // View
            // 
            this.View.Location = new System.Drawing.Point(1, 3);
            this.View.Name = "View";
            this.View.Size = new System.Drawing.Size(760, 570);
            this.View.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.View.TabIndex = 1;
            this.View.TabStop = false;
            // 
            // CameraConfig
            // 
            this.CameraConfig.Controls.Add(this.CameraResetBtn);
            this.CameraConfig.Controls.Add(this.CameraViewVector);
            this.CameraConfig.Controls.Add(this.groupBox1);
            this.CameraConfig.Location = new System.Drawing.Point(186, 56);
            this.CameraConfig.Name = "CameraConfig";
            this.CameraConfig.Size = new System.Drawing.Size(131, 278);
            this.CameraConfig.TabIndex = 2;
            this.CameraConfig.TabStop = false;
            this.CameraConfig.Text = "Camera";
            // 
            // CameraResetBtn
            // 
            this.CameraResetBtn.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.CameraResetBtn.ForeColor = System.Drawing.Color.Coral;
            this.CameraResetBtn.Location = new System.Drawing.Point(6, 241);
            this.CameraResetBtn.Name = "CameraResetBtn";
            this.CameraResetBtn.Size = new System.Drawing.Size(119, 31);
            this.CameraResetBtn.TabIndex = 5;
            this.CameraResetBtn.Text = "Reset";
            this.CameraResetBtn.UseVisualStyleBackColor = false;
            // 
            // CameraViewVector
            // 
            this.CameraViewVector.Controls.Add(this.CameraViewVecZ);
            this.CameraViewVector.Controls.Add(this.CameraViewVecY);
            this.CameraViewVector.Controls.Add(this.CameraViewVecX);
            this.CameraViewVector.Controls.Add(this.label6);
            this.CameraViewVector.Controls.Add(this.label5);
            this.CameraViewVector.Controls.Add(this.label4);
            this.CameraViewVector.Location = new System.Drawing.Point(6, 134);
            this.CameraViewVector.Name = "CameraViewVector";
            this.CameraViewVector.Size = new System.Drawing.Size(119, 101);
            this.CameraViewVector.TabIndex = 4;
            this.CameraViewVector.TabStop = false;
            this.CameraViewVector.Text = "ViewVector";
            // 
            // CameraViewVecZ
            // 
            this.CameraViewVecZ.Location = new System.Drawing.Point(25, 66);
            this.CameraViewVecZ.Name = "CameraViewVecZ";
            this.CameraViewVecZ.Size = new System.Drawing.Size(81, 21);
            this.CameraViewVecZ.TabIndex = 3;
            // 
            // CameraViewVecY
            // 
            this.CameraViewVecY.Location = new System.Drawing.Point(25, 42);
            this.CameraViewVecY.Name = "CameraViewVecY";
            this.CameraViewVecY.Size = new System.Drawing.Size(81, 21);
            this.CameraViewVecY.TabIndex = 2;
            // 
            // CameraViewVecX
            // 
            this.CameraViewVecX.Location = new System.Drawing.Point(25, 17);
            this.CameraViewVecX.Name = "CameraViewVecX";
            this.CameraViewVecX.Size = new System.Drawing.Size(81, 21);
            this.CameraViewVecX.TabIndex = 2;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(8, 69);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(13, 12);
            this.label6.TabIndex = 2;
            this.label6.Text = "Z";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 45);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(13, 12);
            this.label5.TabIndex = 1;
            this.label5.Text = "Y";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 21);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(13, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "X";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cameraZpos);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.cameraYpos);
            this.groupBox1.Controls.Add(this.cameraXpos);
            this.groupBox1.Location = new System.Drawing.Point(6, 20);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(119, 107);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "CameraPos";
            // 
            // cameraZpos
            // 
            this.cameraZpos.Location = new System.Drawing.Point(25, 74);
            this.cameraZpos.Name = "cameraZpos";
            this.cameraZpos.Size = new System.Drawing.Size(81, 21);
            this.cameraZpos.TabIndex = 0;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 75);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(13, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "Z";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(13, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "Y";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(13, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "X";
            // 
            // cameraYpos
            // 
            this.cameraYpos.Location = new System.Drawing.Point(25, 47);
            this.cameraYpos.Name = "cameraYpos";
            this.cameraYpos.Size = new System.Drawing.Size(81, 21);
            this.cameraYpos.TabIndex = 0;
            // 
            // cameraXpos
            // 
            this.cameraXpos.Location = new System.Drawing.Point(25, 20);
            this.cameraXpos.Name = "cameraXpos";
            this.cameraXpos.Size = new System.Drawing.Size(81, 21);
            this.cameraXpos.TabIndex = 0;
            // 
            // TimerStatus
            // 
            this.TimerStatus.Controls.Add(this.TimePass);
            this.TimerStatus.Controls.Add(this.label7);
            this.TimerStatus.Location = new System.Drawing.Point(6, 7);
            this.TimerStatus.Name = "TimerStatus";
            this.TimerStatus.Size = new System.Drawing.Size(162, 43);
            this.TimerStatus.TabIndex = 3;
            this.TimerStatus.TabStop = false;
            this.TimerStatus.Text = "Timer";
            // 
            // TimePass
            // 
            this.TimePass.AutoSize = true;
            this.TimePass.Location = new System.Drawing.Point(77, 20);
            this.TimePass.Name = "TimePass";
            this.TimePass.Size = new System.Drawing.Size(65, 12);
            this.TimePass.TabIndex = 1;
            this.TimePass.Text = "00 : 00 : 00";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 20);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(65, 12);
            this.label7.TabIndex = 0;
            this.label7.Text = "시간 경과 :";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.PlayerStatusReset);
            this.groupBox2.Controls.Add(this.groupBox5);
            this.groupBox2.Controls.Add(this.groupBox4);
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Location = new System.Drawing.Point(6, 56);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(162, 634);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Player";
            // 
            // PlayerStatusReset
            // 
            this.PlayerStatusReset.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.PlayerStatusReset.ForeColor = System.Drawing.Color.Coral;
            this.PlayerStatusReset.Location = new System.Drawing.Point(8, 400);
            this.PlayerStatusReset.Name = "PlayerStatusReset";
            this.PlayerStatusReset.Size = new System.Drawing.Size(148, 31);
            this.PlayerStatusReset.TabIndex = 7;
            this.PlayerStatusReset.Text = "Reset";
            this.PlayerStatusReset.UseVisualStyleBackColor = false;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.IntegratedVelVal);
            this.groupBox5.Controls.Add(this.label17);
            this.groupBox5.Controls.Add(this.PlayerVelocityZ);
            this.groupBox5.Controls.Add(this.PlayerVelocityY);
            this.groupBox5.Controls.Add(this.label18);
            this.groupBox5.Controls.Add(this.PlayerVelocityX);
            this.groupBox5.Controls.Add(this.label19);
            this.groupBox5.Controls.Add(this.label20);
            this.groupBox5.Location = new System.Drawing.Point(8, 264);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(148, 130);
            this.groupBox5.TabIndex = 6;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Velocity";
            // 
            // IntegratedVelVal
            // 
            this.IntegratedVelVal.AutoSize = true;
            this.IntegratedVelVal.Location = new System.Drawing.Point(61, 104);
            this.IntegratedVelVal.Name = "IntegratedVelVal";
            this.IntegratedVelVal.Size = new System.Drawing.Size(11, 12);
            this.IntegratedVelVal.TabIndex = 5;
            this.IntegratedVelVal.Text = "0";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(6, 104);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(37, 12);
            this.label17.TabIndex = 2;
            this.label17.Text = "속도 :";
            // 
            // PlayerVelocityZ
            // 
            this.PlayerVelocityZ.Location = new System.Drawing.Point(25, 70);
            this.PlayerVelocityZ.Name = "PlayerVelocityZ";
            this.PlayerVelocityZ.Size = new System.Drawing.Size(117, 21);
            this.PlayerVelocityZ.TabIndex = 2;
            // 
            // PlayerVelocityY
            // 
            this.PlayerVelocityY.Location = new System.Drawing.Point(25, 43);
            this.PlayerVelocityY.Name = "PlayerVelocityY";
            this.PlayerVelocityY.Size = new System.Drawing.Size(117, 21);
            this.PlayerVelocityY.TabIndex = 3;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(6, 71);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(13, 12);
            this.label18.TabIndex = 2;
            this.label18.Text = "Z";
            // 
            // PlayerVelocityX
            // 
            this.PlayerVelocityX.Location = new System.Drawing.Point(25, 16);
            this.PlayerVelocityX.Name = "PlayerVelocityX";
            this.PlayerVelocityX.Size = new System.Drawing.Size(117, 21);
            this.PlayerVelocityX.TabIndex = 4;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(6, 46);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(13, 12);
            this.label19.TabIndex = 3;
            this.label19.Text = "Y";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(6, 21);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(13, 12);
            this.label20.TabIndex = 4;
            this.label20.Text = "X";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.IntegratedAccelVal);
            this.groupBox4.Controls.Add(this.label14);
            this.groupBox4.Controls.Add(this.PlayerAccelZ);
            this.groupBox4.Controls.Add(this.PlayerAccelY);
            this.groupBox4.Controls.Add(this.label11);
            this.groupBox4.Controls.Add(this.PlayerAccelX);
            this.groupBox4.Controls.Add(this.label12);
            this.groupBox4.Controls.Add(this.label13);
            this.groupBox4.Location = new System.Drawing.Point(8, 128);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(148, 130);
            this.groupBox4.TabIndex = 5;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Accelation";
            // 
            // IntegratedAccelVal
            // 
            this.IntegratedAccelVal.AutoSize = true;
            this.IntegratedAccelVal.Location = new System.Drawing.Point(61, 104);
            this.IntegratedAccelVal.Name = "IntegratedAccelVal";
            this.IntegratedAccelVal.Size = new System.Drawing.Size(11, 12);
            this.IntegratedAccelVal.TabIndex = 5;
            this.IntegratedAccelVal.Text = "0";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(6, 104);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(49, 12);
            this.label14.TabIndex = 2;
            this.label14.Text = "가속도 :";
            // 
            // PlayerAccelZ
            // 
            this.PlayerAccelZ.Location = new System.Drawing.Point(25, 70);
            this.PlayerAccelZ.Name = "PlayerAccelZ";
            this.PlayerAccelZ.Size = new System.Drawing.Size(117, 21);
            this.PlayerAccelZ.TabIndex = 2;
            // 
            // PlayerAccelY
            // 
            this.PlayerAccelY.Location = new System.Drawing.Point(25, 43);
            this.PlayerAccelY.Name = "PlayerAccelY";
            this.PlayerAccelY.Size = new System.Drawing.Size(117, 21);
            this.PlayerAccelY.TabIndex = 3;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 71);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(13, 12);
            this.label11.TabIndex = 2;
            this.label11.Text = "Z";
            // 
            // PlayerAccelX
            // 
            this.PlayerAccelX.Location = new System.Drawing.Point(25, 16);
            this.PlayerAccelX.Name = "PlayerAccelX";
            this.PlayerAccelX.Size = new System.Drawing.Size(117, 21);
            this.PlayerAccelX.TabIndex = 4;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(6, 46);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(13, 12);
            this.label12.TabIndex = 3;
            this.label12.Text = "Y";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(6, 21);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(13, 12);
            this.label13.TabIndex = 4;
            this.label13.Text = "X";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.PlayerPosZ);
            this.groupBox3.Controls.Add(this.PlayerPosY);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.PlayerPosX);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Location = new System.Drawing.Point(8, 20);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(148, 102);
            this.groupBox3.TabIndex = 0;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "PlayerPos";
            // 
            // PlayerPosZ
            // 
            this.PlayerPosZ.Location = new System.Drawing.Point(25, 70);
            this.PlayerPosZ.Name = "PlayerPosZ";
            this.PlayerPosZ.Size = new System.Drawing.Size(117, 21);
            this.PlayerPosZ.TabIndex = 2;
            // 
            // PlayerPosY
            // 
            this.PlayerPosY.Location = new System.Drawing.Point(25, 43);
            this.PlayerPosY.Name = "PlayerPosY";
            this.PlayerPosY.Size = new System.Drawing.Size(117, 21);
            this.PlayerPosY.TabIndex = 3;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 71);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(13, 12);
            this.label8.TabIndex = 2;
            this.label8.Text = "Z";
            // 
            // PlayerPosX
            // 
            this.PlayerPosX.Location = new System.Drawing.Point(25, 16);
            this.PlayerPosX.Name = "PlayerPosX";
            this.PlayerPosX.Size = new System.Drawing.Size(117, 21);
            this.PlayerPosX.TabIndex = 4;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 46);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(13, 12);
            this.label9.TabIndex = 3;
            this.label9.Text = "Y";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 21);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(13, 12);
            this.label10.TabIndex = 4;
            this.label10.Text = "X";
            // 
            // Status
            // 
            this.Status.Controls.Add(this.JSONConfig);
            this.Status.Controls.Add(this.CameraModelStat);
            this.Status.Controls.Add(this.ObjectTool);
            this.Status.Location = new System.Drawing.Point(779, 28);
            this.Status.Name = "Status";
            this.Status.SelectedIndex = 0;
            this.Status.Size = new System.Drawing.Size(473, 722);
            this.Status.TabIndex = 5;
            // 
            // JSONConfig
            // 
            this.JSONConfig.Controls.Add(this.groupBox7);
            this.JSONConfig.Controls.Add(this.groupBox6);
            this.JSONConfig.Location = new System.Drawing.Point(4, 22);
            this.JSONConfig.Name = "JSONConfig";
            this.JSONConfig.Padding = new System.Windows.Forms.Padding(3);
            this.JSONConfig.Size = new System.Drawing.Size(465, 696);
            this.JSONConfig.TabIndex = 1;
            this.JSONConfig.Text = "JSONConfig";
            this.JSONConfig.UseVisualStyleBackColor = true;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.JsonVariables);
            this.groupBox7.Controls.Add(this.JSONKeyLabel);
            this.groupBox7.Controls.Add(this.MdoifyValue);
            this.groupBox7.Controls.Add(this.JSONVarBar);
            this.groupBox7.Location = new System.Drawing.Point(4, 247);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(455, 326);
            this.groupBox7.TabIndex = 1;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Config - Control";
            // 
            // JsonVariables
            // 
            this.JsonVariables.Location = new System.Drawing.Point(7, 20);
            this.JsonVariables.Name = "JsonVariables";
            this.JsonVariables.Size = new System.Drawing.Size(276, 300);
            this.JsonVariables.TabIndex = 7;
            this.JsonVariables.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.TreeViewJsonDataSelected);
            // 
            // JSONKeyLabel
            // 
            this.JSONKeyLabel.AutoSize = true;
            this.JSONKeyLabel.Location = new System.Drawing.Point(290, 21);
            this.JSONKeyLabel.Name = "JSONKeyLabel";
            this.JSONKeyLabel.Size = new System.Drawing.Size(63, 12);
            this.JSONKeyLabel.TabIndex = 6;
            this.JSONKeyLabel.Text = "JSON Key";
            // 
            // MdoifyValue
            // 
            this.MdoifyValue.ForeColor = System.Drawing.Color.RoyalBlue;
            this.MdoifyValue.Location = new System.Drawing.Point(289, 80);
            this.MdoifyValue.Name = "MdoifyValue";
            this.MdoifyValue.Size = new System.Drawing.Size(154, 39);
            this.MdoifyValue.TabIndex = 5;
            this.MdoifyValue.Text = "Modify Value";
            this.MdoifyValue.UseVisualStyleBackColor = true;
            this.MdoifyValue.Click += new System.EventHandler(this.JsonModifyDataBtn);
            // 
            // JSONVarBar
            // 
            this.JSONVarBar.Location = new System.Drawing.Point(289, 53);
            this.JSONVarBar.Name = "JSONVarBar";
            this.JSONVarBar.Size = new System.Drawing.Size(154, 21);
            this.JSONVarBar.TabIndex = 5;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.groupBox9);
            this.groupBox6.Controls.Add(this.RenderStartBtn);
            this.groupBox6.Controls.Add(this.groupBox8);
            this.groupBox6.Location = new System.Drawing.Point(4, 7);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(455, 234);
            this.groupBox6.TabIndex = 0;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Config - Save / Load";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.label15);
            this.groupBox9.Controls.Add(this.JSONSaveFilebtn);
            this.groupBox9.Controls.Add(this.JSONNameToSave);
            this.groupBox9.Location = new System.Drawing.Point(7, 105);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(442, 65);
            this.groupBox9.TabIndex = 3;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "JSON Config Save";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(7, 20);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(315, 12);
            this.label15.TabIndex = 4;
            this.label15.Text = "저장할 Config 파일의 이름을 적어주십시오 (확장자 없이)";
            // 
            // JSONSaveFilebtn
            // 
            this.JSONSaveFilebtn.ForeColor = System.Drawing.Color.RoyalBlue;
            this.JSONSaveFilebtn.Location = new System.Drawing.Point(334, 20);
            this.JSONSaveFilebtn.Name = "JSONSaveFilebtn";
            this.JSONSaveFilebtn.Size = new System.Drawing.Size(102, 39);
            this.JSONSaveFilebtn.TabIndex = 3;
            this.JSONSaveFilebtn.Text = "Save File";
            this.JSONSaveFilebtn.UseVisualStyleBackColor = true;
            this.JSONSaveFilebtn.Click += new System.EventHandler(this.SaveJSONFile);
            // 
            // JSONNameToSave
            // 
            this.JSONNameToSave.Location = new System.Drawing.Point(7, 38);
            this.JSONNameToSave.Name = "JSONNameToSave";
            this.JSONNameToSave.Size = new System.Drawing.Size(321, 21);
            this.JSONNameToSave.TabIndex = 0;
            // 
            // RenderStartBtn
            // 
            this.RenderStartBtn.Enabled = false;
            this.RenderStartBtn.Font = new System.Drawing.Font("Bernard MT Condensed", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RenderStartBtn.ForeColor = System.Drawing.Color.Crimson;
            this.RenderStartBtn.Location = new System.Drawing.Point(14, 176);
            this.RenderStartBtn.Name = "RenderStartBtn";
            this.RenderStartBtn.Size = new System.Drawing.Size(429, 52);
            this.RenderStartBtn.TabIndex = 2;
            this.RenderStartBtn.Text = "S T A R T";
            this.RenderStartBtn.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.JSONLoadFilebtn);
            this.groupBox8.Controls.Add(this.JsonFileList);
            this.groupBox8.Controls.Add(this.JSONSearchFilebtn);
            this.groupBox8.Location = new System.Drawing.Point(7, 21);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(442, 78);
            this.groupBox8.TabIndex = 1;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "JSON Config Path";
            // 
            // JSONLoadFilebtn
            // 
            this.JSONLoadFilebtn.ForeColor = System.Drawing.Color.Maroon;
            this.JSONLoadFilebtn.Location = new System.Drawing.Point(334, 45);
            this.JSONLoadFilebtn.Name = "JSONLoadFilebtn";
            this.JSONLoadFilebtn.Size = new System.Drawing.Size(102, 27);
            this.JSONLoadFilebtn.TabIndex = 2;
            this.JSONLoadFilebtn.Text = "Load File";
            this.JSONLoadFilebtn.UseVisualStyleBackColor = true;
            this.JSONLoadFilebtn.Click += new System.EventHandler(this.LoadJsonFile);
            // 
            // JsonFileList
            // 
            this.JsonFileList.FormattingEnabled = true;
            this.JsonFileList.ItemHeight = 12;
            this.JsonFileList.Location = new System.Drawing.Point(7, 21);
            this.JsonFileList.Name = "JsonFileList";
            this.JsonFileList.Size = new System.Drawing.Size(321, 52);
            this.JsonFileList.TabIndex = 1;
            // 
            // JSONSearchFilebtn
            // 
            this.JSONSearchFilebtn.Font = new System.Drawing.Font("굴림", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.JSONSearchFilebtn.Location = new System.Drawing.Point(334, 20);
            this.JSONSearchFilebtn.Name = "JSONSearchFilebtn";
            this.JSONSearchFilebtn.Size = new System.Drawing.Size(102, 19);
            this.JSONSearchFilebtn.TabIndex = 0;
            this.JSONSearchFilebtn.Text = "Searching";
            this.JSONSearchFilebtn.UseVisualStyleBackColor = true;
            this.JSONSearchFilebtn.Click += new System.EventHandler(this.SearchJsonFile);
            // 
            // CameraModelStat
            // 
            this.CameraModelStat.Controls.Add(this.groupBox11);
            this.CameraModelStat.Controls.Add(this.TimerStatus);
            this.CameraModelStat.Controls.Add(this.CameraConfig);
            this.CameraModelStat.Controls.Add(this.groupBox2);
            this.CameraModelStat.Location = new System.Drawing.Point(4, 22);
            this.CameraModelStat.Name = "CameraModelStat";
            this.CameraModelStat.Padding = new System.Windows.Forms.Padding(3);
            this.CameraModelStat.Size = new System.Drawing.Size(465, 696);
            this.CameraModelStat.TabIndex = 0;
            this.CameraModelStat.Text = "Camera & Model";
            this.CameraModelStat.UseVisualStyleBackColor = true;
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.FPSshow);
            this.groupBox11.Location = new System.Drawing.Point(186, 7);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(136, 43);
            this.groupBox11.TabIndex = 4;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "FPS";
            // 
            // FPSshow
            // 
            this.FPSshow.AutoSize = true;
            this.FPSshow.Location = new System.Drawing.Point(20, 20);
            this.FPSshow.Name = "FPSshow";
            this.FPSshow.Size = new System.Drawing.Size(17, 12);
            this.FPSshow.TabIndex = 1;
            this.FPSshow.Text = "00";
            // 
            // ObjectTool
            // 
            this.ObjectTool.Controls.Add(this.groupBox10);
            this.ObjectTool.Location = new System.Drawing.Point(4, 22);
            this.ObjectTool.Name = "ObjectTool";
            this.ObjectTool.Padding = new System.Windows.Forms.Padding(3);
            this.ObjectTool.Size = new System.Drawing.Size(465, 696);
            this.ObjectTool.TabIndex = 2;
            this.ObjectTool.Text = "ObjectTool";
            this.ObjectTool.UseVisualStyleBackColor = true;
            // 
            // ISSRenderBtn
            // 
            this.ISSRenderBtn.Location = new System.Drawing.Point(270, 432);
            this.ISSRenderBtn.Name = "ISSRenderBtn";
            this.ISSRenderBtn.Size = new System.Drawing.Size(173, 69);
            this.ISSRenderBtn.TabIndex = 1;
            this.ISSRenderBtn.Text = "ObjectRender";
            this.ISSRenderBtn.UseVisualStyleBackColor = true;
            this.ISSRenderBtn.Click += new System.EventHandler(this.ISSRenderStart);
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.groupBox14);
            this.groupBox10.Controls.Add(this.ISSRenderBtn);
            this.groupBox10.Controls.Add(this.groupBox13);
            this.groupBox10.Controls.Add(this.SelectedObjJson);
            this.groupBox10.Controls.Add(this.groupBox12);
            this.groupBox10.Location = new System.Drawing.Point(4, 4);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(455, 686);
            this.groupBox10.TabIndex = 0;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "ObjectPartList";
            // 
            // ObjJsonKey
            // 
            this.ObjJsonKey.AutoSize = true;
            this.ObjJsonKey.Location = new System.Drawing.Point(7, 17);
            this.ObjJsonKey.Name = "ObjJsonKey";
            this.ObjJsonKey.Size = new System.Drawing.Size(63, 12);
            this.ObjJsonKey.TabIndex = 9;
            this.ObjJsonKey.Text = "JSON Key";
            // 
            // button3
            // 
            this.button3.ForeColor = System.Drawing.Color.RoyalBlue;
            this.button3.Location = new System.Drawing.Point(6, 76);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(176, 39);
            this.button3.TabIndex = 7;
            this.button3.Text = "Modify Value";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.ModifyObjValue);
            // 
            // ObjJsonValue
            // 
            this.ObjJsonValue.Location = new System.Drawing.Point(6, 49);
            this.ObjJsonValue.Name = "ObjJsonValue";
            this.ObjJsonValue.Size = new System.Drawing.Size(176, 21);
            this.ObjJsonValue.TabIndex = 8;
            // 
            // groupBox13
            // 
            this.groupBox13.Controls.Add(this.MeshFIleList);
            this.groupBox13.Controls.Add(this.button2);
            this.groupBox13.Controls.Add(this.button1);
            this.groupBox13.Location = new System.Drawing.Point(7, 322);
            this.groupBox13.Name = "groupBox13";
            this.groupBox13.Size = new System.Drawing.Size(248, 179);
            this.groupBox13.TabIndex = 6;
            this.groupBox13.TabStop = false;
            this.groupBox13.Text = "LoadRealMesh";
            // 
            // MeshFIleList
            // 
            this.MeshFIleList.FormattingEnabled = true;
            this.MeshFIleList.ItemHeight = 12;
            this.MeshFIleList.Location = new System.Drawing.Point(6, 20);
            this.MeshFIleList.Name = "MeshFIleList";
            this.MeshFIleList.Size = new System.Drawing.Size(236, 76);
            this.MeshFIleList.TabIndex = 5;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(6, 139);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(236, 32);
            this.button2.TabIndex = 4;
            this.button2.Text = "Load Mesh";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.LoadMeshBtn);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 104);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(236, 29);
            this.button1.TabIndex = 3;
            this.button1.Text = "Search Mesh";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.SearchMeshBtn);
            // 
            // SelectedObjJson
            // 
            this.SelectedObjJson.Location = new System.Drawing.Point(7, 20);
            this.SelectedObjJson.Name = "SelectedObjJson";
            this.SelectedObjJson.Size = new System.Drawing.Size(248, 278);
            this.SelectedObjJson.TabIndex = 6;
            this.SelectedObjJson.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.ObjJsonSelected);
            // 
            // groupBox12
            // 
            this.groupBox12.Controls.Add(this.LoadObjDataBtn);
            this.groupBox12.Controls.Add(this.ModelNameTxt);
            this.groupBox12.Location = new System.Drawing.Point(261, 20);
            this.groupBox12.Name = "groupBox12";
            this.groupBox12.Size = new System.Drawing.Size(188, 78);
            this.groupBox12.TabIndex = 5;
            this.groupBox12.TabStop = false;
            this.groupBox12.Text = "LoadJsonModelData";
            // 
            // LoadObjDataBtn
            // 
            this.LoadObjDataBtn.Location = new System.Drawing.Point(6, 43);
            this.LoadObjDataBtn.Name = "LoadObjDataBtn";
            this.LoadObjDataBtn.Size = new System.Drawing.Size(176, 29);
            this.LoadObjDataBtn.TabIndex = 3;
            this.LoadObjDataBtn.Text = "Load Data";
            this.LoadObjDataBtn.UseVisualStyleBackColor = true;
            this.LoadObjDataBtn.Click += new System.EventHandler(this.LoadDataFromTree);
            // 
            // ModelNameTxt
            // 
            this.ModelNameTxt.Location = new System.Drawing.Point(6, 16);
            this.ModelNameTxt.Name = "ModelNameTxt";
            this.ModelNameTxt.Size = new System.Drawing.Size(176, 21);
            this.ModelNameTxt.TabIndex = 2;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tab_GameRender);
            this.tabControl1.Controls.Add(this.tab_ISSPartRender);
            this.tabControl1.Location = new System.Drawing.Point(0, 28);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(773, 722);
            this.tabControl1.TabIndex = 7;
            // 
            // tab_GameRender
            // 
            this.tab_GameRender.Controls.Add(this.View);
            this.tab_GameRender.Location = new System.Drawing.Point(4, 22);
            this.tab_GameRender.Name = "tab_GameRender";
            this.tab_GameRender.Padding = new System.Windows.Forms.Padding(3);
            this.tab_GameRender.Size = new System.Drawing.Size(765, 696);
            this.tab_GameRender.TabIndex = 0;
            this.tab_GameRender.Text = "GameRender";
            this.tab_GameRender.UseVisualStyleBackColor = true;
            // 
            // tab_ISSPartRender
            // 
            this.tab_ISSPartRender.Controls.Add(this.ObjectView);
            this.tab_ISSPartRender.Location = new System.Drawing.Point(4, 22);
            this.tab_ISSPartRender.Name = "tab_ISSPartRender";
            this.tab_ISSPartRender.Padding = new System.Windows.Forms.Padding(3);
            this.tab_ISSPartRender.Size = new System.Drawing.Size(765, 696);
            this.tab_ISSPartRender.TabIndex = 1;
            this.tab_ISSPartRender.Text = "ISSPartRender";
            this.tab_ISSPartRender.UseVisualStyleBackColor = true;
            // 
            // ObjectView
            // 
            this.ObjectView.Location = new System.Drawing.Point(3, 3);
            this.ObjectView.Name = "ObjectView";
            this.ObjectView.Size = new System.Drawing.Size(760, 680);
            this.ObjectView.TabIndex = 5;
            this.ObjectView.TabStop = false;
            this.ObjectView.Click += new System.EventHandler(this.ISSPartRenderClick);
            // 
            // groupBox14
            // 
            this.groupBox14.Controls.Add(this.ObjJsonKey);
            this.groupBox14.Controls.Add(this.ObjJsonValue);
            this.groupBox14.Controls.Add(this.button3);
            this.groupBox14.Location = new System.Drawing.Point(261, 177);
            this.groupBox14.Name = "groupBox14";
            this.groupBox14.Size = new System.Drawing.Size(188, 121);
            this.groupBox14.TabIndex = 6;
            this.groupBox14.TabStop = false;
            this.groupBox14.Text = "JSONModify";
            // 
            // IndependentGameTool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 762);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.Status);
            this.Name = "IndependentGameTool";
            this.Text = "skyLab";
            ((System.ComponentModel.ISupportInitialize)(this.View)).EndInit();
            this.CameraConfig.ResumeLayout(false);
            this.CameraViewVector.ResumeLayout(false);
            this.CameraViewVector.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.TimerStatus.ResumeLayout(false);
            this.TimerStatus.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.Status.ResumeLayout(false);
            this.JSONConfig.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.CameraModelStat.ResumeLayout(false);
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.ObjectTool.ResumeLayout(false);
            this.groupBox10.ResumeLayout(false);
            this.groupBox13.ResumeLayout(false);
            this.groupBox12.ResumeLayout(false);
            this.groupBox12.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tab_GameRender.ResumeLayout(false);
            this.tab_ISSPartRender.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.ObjectView)).EndInit();
            this.groupBox14.ResumeLayout(false);
            this.groupBox14.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox View;
        private System.Windows.Forms.GroupBox CameraConfig;
        private System.Windows.Forms.TextBox cameraXpos;
        private System.Windows.Forms.TextBox cameraYpos;
        private System.Windows.Forms.TextBox cameraZpos;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox CameraViewVector;
        private System.Windows.Forms.TextBox CameraViewVecZ;
        private System.Windows.Forms.TextBox CameraViewVecY;
        private System.Windows.Forms.TextBox CameraViewVecX;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button CameraResetBtn;
        private System.Windows.Forms.GroupBox TimerStatus;
        private System.Windows.Forms.Label TimePass;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox PlayerAccelZ;
        private System.Windows.Forms.TextBox PlayerAccelY;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox PlayerAccelX;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox PlayerPosZ;
        private System.Windows.Forms.TextBox PlayerPosY;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox PlayerPosX;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label IntegratedVelVal;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox PlayerVelocityZ;
        private System.Windows.Forms.TextBox PlayerVelocityY;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox PlayerVelocityX;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label IntegratedAccelVal;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button PlayerStatusReset;
        private System.Windows.Forms.TabControl Status;
        private System.Windows.Forms.TabPage CameraModelStat;
        private System.Windows.Forms.TabPage JSONConfig;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Button JSONLoadFilebtn;
        private System.Windows.Forms.ListBox JsonFileList;
        private System.Windows.Forms.Button JSONSearchFilebtn;
        private System.Windows.Forms.Button RenderStartBtn;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.Button JSONSaveFilebtn;
        private System.Windows.Forms.TextBox JSONNameToSave;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox JSONVarBar;
        private System.Windows.Forms.Button MdoifyValue;
        private System.Windows.Forms.Label JSONKeyLabel;
        private System.Windows.Forms.TabPage ObjectTool;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Label FPSshow;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tab_GameRender;
        private System.Windows.Forms.TabPage tab_ISSPartRender;
        private System.Windows.Forms.PictureBox ObjectView;
        private System.Windows.Forms.Button ISSRenderBtn;
        private System.Windows.Forms.TreeView JsonVariables;
        private System.Windows.Forms.GroupBox groupBox12;
        private System.Windows.Forms.Button LoadObjDataBtn;
        private System.Windows.Forms.TextBox ModelNameTxt;
        private System.Windows.Forms.TreeView SelectedObjJson;
        private System.Windows.Forms.GroupBox groupBox13;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ListBox MeshFIleList;
        private System.Windows.Forms.Label ObjJsonKey;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox ObjJsonValue;
        private System.Windows.Forms.GroupBox groupBox14;
    }
}

