﻿namespace GameTool
{
    partial class skyLabTool
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.versionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
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
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
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
            this.CameraModelStat = new System.Windows.Forms.TabPage();
            this.JSONConfig = new System.Windows.Forms.TabPage();
            this.RenderOnOffBtn = new System.Windows.Forms.Button();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.JsonSearching = new System.Windows.Forms.Button();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.JsonFileList = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.ConfigRestartBtn = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
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
            this.CameraModelStat.SuspendLayout();
            this.JSONConfig.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1264, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.loadToolStripMenuItem,
            this.importToolStripMenuItem,
            this.exportToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(110, 22);
            this.newToolStripMenuItem.Text = "New";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(110, 22);
            this.saveToolStripMenuItem.Text = "Save";
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(110, 22);
            this.loadToolStripMenuItem.Text = "Load";
            // 
            // importToolStripMenuItem
            // 
            this.importToolStripMenuItem.Name = "importToolStripMenuItem";
            this.importToolStripMenuItem.Size = new System.Drawing.Size(110, 22);
            this.importToolStripMenuItem.Text = "Import";
            // 
            // exportToolStripMenuItem
            // 
            this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
            this.exportToolStripMenuItem.Size = new System.Drawing.Size(110, 22);
            this.exportToolStripMenuItem.Text = "Export";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(110, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.versionToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // versionToolStripMenuItem
            // 
            this.versionToolStripMenuItem.Name = "versionToolStripMenuItem";
            this.versionToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.versionToolStripMenuItem.Text = "Version";
            // 
            // View
            // 
            this.View.Location = new System.Drawing.Point(13, 28);
            this.View.Name = "View";
            this.View.Size = new System.Drawing.Size(760, 570);
            this.View.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.View.TabIndex = 1;
            this.View.TabStop = false;
            this.View.MouseEnter += new System.EventHandler(this.ViewMouseEnver);
            this.View.MouseLeave += new System.EventHandler(this.ViewMouseLeave);
            this.View.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ViewMouseMove);
            this.View.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.InputProc);
            // 
            // CameraConfig
            // 
            this.CameraConfig.Controls.Add(this.CameraResetBtn);
            this.CameraConfig.Controls.Add(this.CameraViewVector);
            this.CameraConfig.Controls.Add(this.groupBox1);
            this.CameraConfig.Location = new System.Drawing.Point(328, 7);
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
            this.CameraResetBtn.Click += new System.EventHandler(this.ResetCamera);
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
            this.TimerStatus.Size = new System.Drawing.Size(174, 43);
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
            this.groupBox2.Size = new System.Drawing.Size(174, 430);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Player";
            // 
            // PlayerStatusReset
            // 
            this.PlayerStatusReset.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.PlayerStatusReset.ForeColor = System.Drawing.Color.Coral;
            this.PlayerStatusReset.Location = new System.Drawing.Point(8, 393);
            this.PlayerStatusReset.Name = "PlayerStatusReset";
            this.PlayerStatusReset.Size = new System.Drawing.Size(160, 31);
            this.PlayerStatusReset.TabIndex = 7;
            this.PlayerStatusReset.Text = "Reset";
            this.PlayerStatusReset.UseVisualStyleBackColor = false;
            this.PlayerStatusReset.Click += new System.EventHandler(this.ResetPlayerStatus);
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
            this.groupBox5.Size = new System.Drawing.Size(160, 130);
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
            this.PlayerVelocityZ.Size = new System.Drawing.Size(129, 21);
            this.PlayerVelocityZ.TabIndex = 2;
            // 
            // PlayerVelocityY
            // 
            this.PlayerVelocityY.Location = new System.Drawing.Point(25, 43);
            this.PlayerVelocityY.Name = "PlayerVelocityY";
            this.PlayerVelocityY.Size = new System.Drawing.Size(129, 21);
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
            this.PlayerVelocityX.Size = new System.Drawing.Size(129, 21);
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
            this.groupBox4.Size = new System.Drawing.Size(160, 130);
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
            this.PlayerAccelZ.Size = new System.Drawing.Size(129, 21);
            this.PlayerAccelZ.TabIndex = 2;
            // 
            // PlayerAccelY
            // 
            this.PlayerAccelY.Location = new System.Drawing.Point(25, 43);
            this.PlayerAccelY.Name = "PlayerAccelY";
            this.PlayerAccelY.Size = new System.Drawing.Size(129, 21);
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
            this.PlayerAccelX.Size = new System.Drawing.Size(129, 21);
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
            this.groupBox3.Size = new System.Drawing.Size(160, 102);
            this.groupBox3.TabIndex = 0;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "PlayerPos";
            // 
            // PlayerPosZ
            // 
            this.PlayerPosZ.Location = new System.Drawing.Point(25, 70);
            this.PlayerPosZ.Name = "PlayerPosZ";
            this.PlayerPosZ.Size = new System.Drawing.Size(129, 21);
            this.PlayerPosZ.TabIndex = 2;
            // 
            // PlayerPosY
            // 
            this.PlayerPosY.Location = new System.Drawing.Point(25, 43);
            this.PlayerPosY.Name = "PlayerPosY";
            this.PlayerPosY.Size = new System.Drawing.Size(129, 21);
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
            this.PlayerPosX.Size = new System.Drawing.Size(129, 21);
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
            this.Status.Controls.Add(this.CameraModelStat);
            this.Status.Controls.Add(this.JSONConfig);
            this.Status.Location = new System.Drawing.Point(779, 28);
            this.Status.Name = "Status";
            this.Status.SelectedIndex = 0;
            this.Status.Size = new System.Drawing.Size(473, 722);
            this.Status.TabIndex = 5;
            // 
            // CameraModelStat
            // 
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
            // RenderOnOffBtn
            // 
            this.RenderOnOffBtn.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.RenderOnOffBtn.Location = new System.Drawing.Point(13, 605);
            this.RenderOnOffBtn.Name = "RenderOnOffBtn";
            this.RenderOnOffBtn.Size = new System.Drawing.Size(99, 23);
            this.RenderOnOffBtn.TabIndex = 6;
            this.RenderOnOffBtn.Text = "Render On/Off";
            this.RenderOnOffBtn.UseVisualStyleBackColor = true;
            this.RenderOnOffBtn.Click += new System.EventHandler(this.RenderOnOff);
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.ConfigRestartBtn);
            this.groupBox6.Controls.Add(this.groupBox8);
            this.groupBox6.Location = new System.Drawing.Point(4, 7);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(455, 250);
            this.groupBox6.TabIndex = 0;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Config - Input";
            // 
            // groupBox7
            // 
            this.groupBox7.Location = new System.Drawing.Point(4, 263);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(455, 114);
            this.groupBox7.TabIndex = 1;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Config - Output";
            // 
            // JsonSearching
            // 
            this.JsonSearching.Font = new System.Drawing.Font("굴림", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.JsonSearching.Location = new System.Drawing.Point(334, 20);
            this.JsonSearching.Name = "JsonSearching";
            this.JsonSearching.Size = new System.Drawing.Size(102, 19);
            this.JsonSearching.TabIndex = 0;
            this.JsonSearching.Text = "Searching";
            this.JsonSearching.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.button1);
            this.groupBox8.Controls.Add(this.JsonFileList);
            this.groupBox8.Controls.Add(this.JsonSearching);
            this.groupBox8.Location = new System.Drawing.Point(7, 21);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(442, 78);
            this.groupBox8.TabIndex = 1;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "JSON Config Path";
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
            // button1
            // 
            this.button1.ForeColor = System.Drawing.Color.Maroon;
            this.button1.Location = new System.Drawing.Point(334, 45);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(102, 27);
            this.button1.TabIndex = 2;
            this.button1.Text = "Load File";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // ConfigRestartBtn
            // 
            this.ConfigRestartBtn.Location = new System.Drawing.Point(341, 192);
            this.ConfigRestartBtn.Name = "ConfigRestartBtn";
            this.ConfigRestartBtn.Size = new System.Drawing.Size(102, 52);
            this.ConfigRestartBtn.TabIndex = 2;
            this.ConfigRestartBtn.Text = "Restart";
            this.ConfigRestartBtn.UseVisualStyleBackColor = true;
            // 
            // skyLabTool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 762);
            this.Controls.Add(this.RenderOnOffBtn);
            this.Controls.Add(this.Status);
            this.Controls.Add(this.View);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "skyLabTool";
            this.Text = "skyLab";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
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
            this.CameraModelStat.ResumeLayout(false);
            this.JSONConfig.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem versionToolStripMenuItem;
        private System.Windows.Forms.PictureBox View;
        private System.Windows.Forms.GroupBox CameraConfig;
        private System.Windows.Forms.TextBox cameraXpos;
        private System.Windows.Forms.TextBox cameraYpos;
        private System.Windows.Forms.TextBox cameraZpos;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
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
        private System.Windows.Forms.Button RenderOnOffBtn;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ListBox JsonFileList;
        private System.Windows.Forms.Button JsonSearching;
        private System.Windows.Forms.Button ConfigRestartBtn;
    }
}

