#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

std::string path;       //Video file path.
QString folderName;     //The folder's path where the pictures are saved.
bool videoSelected = false;     //Bool to check if a file has been selected.
bool folderSelected = false;        //Bool to check if a folder has been selected.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Starting values for the ui elements:
    ui->setupUi(this);
    ui->frequencySpinBox->setMaximum(1000);
    ui->frequencySpinBox->setValue(5);
    ui->formatComboBox->addItem("png");
    ui->formatComboBox->addItem("jpg");
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(false);

    //QSettings for the project:
    QSettings settings("CrazyCompany", "VideoDeconstructorWidget");
    QString lastFolder = settings.value("lastFolder", "").toString();       //lastFolder is used to save the folder location from last time.
    if (!lastFolder.isEmpty()) {        //Checks if the lastFolder holds a path.
        folderName = lastFolder;        //The current folderName is updated.
        ui->outputPathLabel->setText(lastFolder);       //Label is updated.
        folderSelected = true;      //Sets selected to true.
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Function for when select video button is pressed. Opens window to select a file from and sets variables right for later.
void MainWindow::on_selectVideoButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choose video", "", "Video Files (*.mp4 *.avi *.mov)");       //Settings for file selection. Only accepts video files.
    if (fileName.isEmpty()) {       //If no video was selected,
        ui->videoPathLabel->setText(fileName);  //Label is updated to empty.
        videoSelected = false;      //Bool set to false.
        return;     //Returns from the clicked function.
    }
    //If a video file was found:
    ui->videoPathLabel->setText(fileName);       //Label is updated to the file's path.
    path = fileName.toStdString();      //fileName QString is converted to std string variable so openCV can read it and saved to path.
    videoSelected = true;       //Bool set to true.
}


//Function for when select folder button is pressed. Opens a window to select a folder from and sets necessary variables right for later.
void MainWindow::on_selectOutputFolderButton_clicked() {
    folderName = QFileDialog::getExistingDirectory(this, "Choose folder", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);        //Settings for folder selection. Only shows directories to select from.
    if (folderName.isEmpty()) {     //Checks if a folder was found.
        folderSelected = false;     //If not bool is set to false.
        ui->outputPathLabel->setText(folderName);       //Label is updated to empty.
        return;     //Returns from the function.
    }
    //If a folder was found:
    ui->outputPathLabel->setText(folderName);       //Label is updated to the folder's path.
    QSettings settings("CrazyCompany", "VideoDeconstructorWidget");     //QSettings are declared,
    settings.setValue("lastFolder", folderName);        //then the settings are used to save the folderName to the lastFolder variable for next time.
    folderSelected = true;      //Selected is set to true.
}


bool looping = false;       //Bool for checking if there is an ongoing video deconstruction loop happening.
void prepareFolder();       //Function to delete old frame images from the selected folder.
void deconstructVideo();        //The actual video deconstruct function.

//Function for when the start button is pressed. Uses previously set variables and starts the picture deconstruction program:
void MainWindow::on_startButton_clicked() {
    if (videoSelected && folderSelected && !looping) {      //First checks if requirements for starting are met and that there is no deconstruction loop happening.
        if (ui->clearFolderCheckBox->isChecked()) {     //Checks if the checkbox for clearing the folder is checked.
            prepareFolder();
        }
        deconstructVideo();
    }
    else if (!videoSelected || !folderSelected) {       //If either of the selection bools are false,
        QMessageBox::warning(this, "Warning", "Fill the file and folder paths!");       //A warning message is given to tell the user about it.
    }
    else if (looping) {     //If the reason fro failure was that there was an old program looping,
        looping = false;        //It is stopped instead of starting a new one.
        //Progress bar is reset:
        ui->progressBar->setValue(0);
        ui->progressBar->setTextVisible(false);
    }
}

//Function to delete old frame images from the selected folder:
void MainWindow::prepareFolder() {
    QDir folder(folderName);        //QDir variable for the folder that the images are being saved in.
    if (!folder.isEmpty()) {        //If the directory isn't empty,
        //PNG and JPG images from the directory are deleted:
        QStringList pngFiles = folder.entryList(QStringList() << "frame_*.png", QDir::Files);       //First a QStringList is declared by searching all the files with frame_*.png names. (* means anything in between)
        for (const QString &fileName : pngFiles) {      //Then for all the files in the string list,
            QFile file(folder.filePath(fileName));      //The files with those names are transformed into QFile form,
            file.remove();      //And then they are removed.
        }
        //Same code as above, but for JPG images:
        QStringList jpgFiles = folder.entryList(QStringList() << "frame_*.jpg", QDir::Files);
        for (const QString &fileName : jpgFiles) {
            QFile file(folder.filePath(fileName));
            file.remove();
        }
    }
}

//The actual video deconstruction function. Uses all previously set variables and openCV to deconstruct the selected video into images into the selected folder:
void MainWindow::deconstructVideo() {
    cv::VideoCapture cap(path);     //openCV videocapture cap is declared that uses the video selected from earlier.
    if (!cap.isOpened()) {      //Checks if the video was opened with cv correctly.
        return;
    }
    looping = true;     //Looping is set to true to indicate a starting loop.
    cv::Mat frame;      //openCV variable for the frames being handled.
    int frameNumber = 1;        //Increasing number for the file names.
    int frameGap = ui->frequencySpinBox->value();       //frameGap is used to determine the gap between saved frames.
    ui->startButton->setText("Stop");       //Start button text is changed to indicate that pressing again will stop the loop.
    ui->progressBar->setMaximum(cap.get(cv::CAP_PROP_FRAME_COUNT) / frameGap);      //Progress bar's maximum value is equal to the amount of frames divided by frameGap.
    ui->progressBar->setTextVisible(true);
    QString format = ui->formatComboBox->currentText();     //Format is retrieved from the comboBox.

    //For loop that goes through frames from the video with frameGaps in between:
    for (int i = 0; i < cap.get(cv::CAP_PROP_FRAME_COUNT); i += frameGap) {
        if (!looping) {     //If looping is ever set to false the loop is broken. (stop button)
            break;
        }
        cap.set(cv::CAP_PROP_POS_FRAMES, i);        //Sets the processed frame using i variable.
        if (cap.read(frame)) {      //The frame is read using openCV.
            //Optional debug messages:
            qDebug() << "Frame read. Size: " << frame.cols << "x" << frame.rows;
        }
        else {
            qDebug() << "No frame found!";
            break;      //If no frames are found the loop is broken.
        }

        QString outputFilePath = folderName + "/frame_" + QString::number(frameNumber) + "." + format;      //The filepath and name for the new image deconstructed from the video.

        if (cv::imwrite(outputFilePath.toUtf8().constData(), frame)) {      //The new image is saved to the folder location from outputFilePath with a name also given by it.
            //Debug messages:
            qDebug() << "Frame saved to:" << outputFilePath;
        } else {
            qDebug() << "File path was not found!";
            break;      //If the file couldn't be saved the loop is broken.
        }
        ui->progressBar->setValue(frameNumber);     //Progress bar is updated using the current frameNumber.
        frameNumber++;      //The frame number is increased for the next image.
        QCoreApplication::processEvents();      //Events are processed to update the progress bar and ui.
    }
    cap.release();      //The video is released.
    looping = false;        //Looping is set to false to indicate no ongoing looping anymore.
    ui->startButton->setText("Start");      //StartButton is changed back to normal.
}
