namespace GameTool
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
            this.label7 = new System.Windows.Forms.Label();
            this.TimePass = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.View)).BeginInit();
            this.CameraConfig.SuspendLayout();
            this.CameraViewVector.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.TimerStatus.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1088, 24);
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
            this.View.Size = new System.Drawing.Size(640, 480);
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
            this.CameraConfig.Location = new System.Drawing.Point(933, 28);
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
            this.TimerStatus.Location = new System.Drawing.Point(753, 28);
            this.TimerStatus.Name = "TimerStatus";
            this.TimerStatus.Size = new System.Drawing.Size(174, 43);
            this.TimerStatus.TabIndex = 3;
            this.TimerStatus.TabStop = false;
            this.TimerStatus.Text = "Timer";
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
            // TimePass
            // 
            this.TimePass.AutoSize = true;
            this.TimePass.Location = new System.Drawing.Point(77, 20);
            this.TimePass.Name = "TimePass";
            this.TimePass.Size = new System.Drawing.Size(65, 12);
            this.TimePass.TabIndex = 1;
            this.TimePass.Text = "00 : 00 : 00";
            // 
            // skyLabTool
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1088, 684);
            this.Controls.Add(this.TimerStatus);
            this.Controls.Add(this.CameraConfig);
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
    }
}

