#include "mainwindow.h"
#include <map>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPrintDialog>
#include <QPrinter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);

    ui->CGPAcomboBox->addItem("No");
    ui->CGPAcomboBox->addItem("Yes");

    for (int var = 1; var < 16; ++var) {
        ui->CoursescomboBox->addItem(QString::number(var));
    }

    ui->CalculatepushButton->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createCourseInputBox(int LayoutCount){


    if(ui->CGPAcomboBox->currentText() == "Yes"){

    cucp.FormerCULabel = new QLabel;
    cucp.FormerCULineEdit = new QLineEdit;
    cucp.FormerCPLabel = new QLabel;
    cucp.FormerCPLineEdit = new QLineEdit;

    cucp.FormerCULabel->setText("Former CU");
    cucp.FormerCPLabel->setText("Former CP");

    ui->cuandsplayout->addWidget(cucp.FormerCULabel);
    ui->cuandsplayout->addWidget(cucp.FormerCULineEdit);
    ui->cuandsplayout->addWidget(cucp.FormerCPLabel);
    ui->cuandsplayout->addWidget(cucp.FormerCPLineEdit);

}

    layoutArray.resize(LayoutCount);

    // populate layoutArray
    for(int i = 0; i<LayoutCount; i++)
        {

        QHBoxLayout* layout=this->findChild<QHBoxLayout*>(QString("inputLayout_%1").arg(i));
        if(layout==nullptr)
            {
            // not found
            continue;
            }
        layoutArray[i].layout=layout;
        layoutArray[i].CourseCodeLabel=new QLabel;
        layoutArray[i].CourseCodeLabel->setText("Course Code");
        layoutArray[i].CourseCodeLineEdit=new QLineEdit;
        layoutArray[i].CourseGradeLabel=new QLabel;
        layoutArray[i].CourseGradeLabel->setText("Grade");
        layoutArray[i].CourseGradeComboBox=new QComboBox;
        layoutArray[i].CourseGradeComboBox->addItem("A");
        layoutArray[i].CourseGradeComboBox->addItem("B");
        layoutArray[i].CourseGradeComboBox->addItem("C");
        layoutArray[i].CourseGradeComboBox->addItem("D");
        layoutArray[i].CourseGradeComboBox->addItem("E");
        layoutArray[i].CourseGradeComboBox->addItem("F");
        layoutArray[i].CourseUnitLabel = new QLabel;
        layoutArray[i].CourseUnitLabel->setText("Unit");
        layoutArray[i].CourseUnitComboBox = new QComboBox;
        layoutArray[i].CourseUnitComboBox->addItem(QString::number(1));
        layoutArray[i].CourseUnitComboBox->addItem(QString::number(2));
        layoutArray[i].CourseUnitComboBox->addItem(QString::number(3));
        layoutArray[i].CourseUnitComboBox->addItem(QString::number(4));


        // populate QLayout
        layout->addWidget(layoutArray[i].CourseCodeLabel);
        layout->addWidget(layoutArray[i].CourseCodeLineEdit);
        layout->addWidget(layoutArray[i].CourseGradeLabel);
        layout->addWidget(layoutArray[i].CourseGradeComboBox);
        layout->addWidget(layoutArray[i].CourseUnitLabel);
        layout->addWidget(layoutArray[i].CourseUnitComboBox);
        }


    ui->CalculatepushButton->setVisible(true);

}

void MainWindow::calculateGrade(int layoutCount){

    result += QString("<center><h1>RESULTS</h1></center><br>"
                             "<h2>NAME : %1</h2>\n"
                             "<h2>LEVEL : %2</h2><br>"
                            "<font size = \"5\">"
                             "<table border = 1 width = \"100%\">"
                      "<tr><th>Course Code</th><th>Grade</th><th>Unit</th></tr>").arg(ui->NamelineEdit->text(), ui->lineEdit_2->text());

    std::map<QString, int> courseGradeLabels{
        {"A", 5},
        {"B", 4},
        {"C", 3},
        {"D", 2},
        {"E", 1},
        {"F", 0}
    };

// STUDENT WITH PREVIOUS CGPA

    if(ui->CGPAcomboBox->currentText() == "Yes"){
        for (int i = 0; i < layoutCount; i++) {
            result += QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>").arg(layoutArray[i].CourseCodeLineEdit->text(), layoutArray[i].CourseGradeComboBox->currentText(), layoutArray[i].CourseUnitComboBox->currentText());
            qDebug() << layoutArray[i].CourseCodeLineEdit->text() << layoutArray[i].CourseGradeComboBox->currentText() << layoutArray[i].CourseUnitComboBox->currentText();
            SU+=layoutArray[i].CourseUnitComboBox->currentText().toInt();
            SP+=(layoutArray[i].CourseUnitComboBox->currentText().toInt() * courseGradeLabels[layoutArray[i].CourseGradeComboBox->currentText()]);
        }
        result += QString("</table></font>");

        qDebug() << "Sum of Unit SU = " << SU;
        qDebug() << "Sum of Point SP = " << SP;

        CU = cucp.FormerCULineEdit->text().toInt();
        CP = cucp.FormerCPLineEdit->text().toInt();

        qDebug() << "Cummulative Unit CU = " << CU;
        qDebug() << "Cummulative Point CP = " << CP;

        CGPA = static_cast<float>(CP+SP)/(CU+SU);

        result += QString("<br><h3>Sum of Unit SU = %1</h3>\n"
                          "<h3>Sum of Point SP = %2</h3>\n"
                          "<h3>Cummulative Unit CU = %3</h3>\n"
                          "<h3>Cummulative Point CP = %4</h3>\n"
                          "<h3>Current GPA = %5</h3>\n"
                          "<h3>CGPA = %6</h3>").arg(SU).arg(SP).arg(CU+SU).arg(CP+SP).arg(static_cast<float>(SP)/SU).arg(CGPA);

        qDebug() << "Current GPA = " << static_cast<float>(SP)/SU;
        qDebug() << "CGPA = " << CGPA;

    }
    else{   // NO PREVIOUS CGPA
        for (int i = 0; i < layoutCount; i++) {
            result += QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>").arg(layoutArray[i].CourseCodeLineEdit->text(), layoutArray[i].CourseGradeComboBox->currentText(), layoutArray[i].CourseUnitComboBox->currentText());
            qDebug() << layoutArray[i].CourseCodeLineEdit->text() << layoutArray[i].CourseGradeComboBox->currentText() << layoutArray[i].CourseUnitComboBox->currentText();
            CU+=layoutArray[i].CourseUnitComboBox->currentText().toInt();
            CP+=(layoutArray[i].CourseUnitComboBox->currentText().toInt() * courseGradeLabels[layoutArray[i].CourseGradeComboBox->currentText()]);
        }
        result += QString("</table></font>");

        result += QString("<br><h3>Cummulative Unit CU = %1</h3>\n"
                          "<h3>Cummulative Point CP = %2</h3>\n"
                          "<h3>Current GPA = %3</h3>").arg(CU).arg(CP).arg(static_cast<float>(CP)/CU);

        qDebug() << "Cummulative Unit CU = " << CU;
        qDebug() << "Cummulative Point CP = " << CP;
        qDebug() << "Current GPA = " << static_cast<float>(CP)/CU;
    }

}


void MainWindow::on_CoursespushButton_clicked()
{ 
    createCourseInputBox(ui->CoursescomboBox->currentText().toInt());
}

void MainWindow::on_CalculatepushButton_clicked()
{

    calculateGrade(ui->CoursescomboBox->currentText().toInt());
    ui->textEdit->setText(result);

}


void MainWindow::on_PrintpushButton_clicked()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec() == QDialog::Rejected){
        return;
    }
    else{
        ui->textEdit->print(&printer);
    }
}


void MainWindow::on_SavepushButton_clicked()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec() == QDialog::Rejected){
        return;
    }
    else{
        ui->textEdit->print(&printer);
    }
}


void MainWindow::on_ClearpushButton_clicked()
{
    newWindow = new MainWindow(this);
    newWindow->show();
    hide();
}

