#pragma once

#include <QMainWindow>
#include <QVector>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QLabel;
class QComboBox;
class QLineEdit;

QT_END_NAMESPACE

struct LayoutWidgets
{
        QHBoxLayout* layout;
        QLabel*     CourseCodeLabel;
        QLineEdit*  CourseCodeLineEdit;
        QLabel*     CourseGradeLabel;
        QComboBox*  CourseGradeComboBox;
        QLabel*     CourseUnitLabel;
        QComboBox*  CourseUnitComboBox;

};

struct CUCP
{
    QLabel*     FormerCULabel;
    QLineEdit*  FormerCULineEdit;
    QLabel*     FormerCPLabel;
    QLineEdit*  FormerCPLineEdit;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);


    int CU{0};
    int CP{0};

    int SU{0};
    int SP{0};

    float GPA{0.0};
    float CGPA{0.0};

    void createCourseInputBox(int LayoutCount);
    void calculateGrade(int layoutCount);


    ~MainWindow();

private slots:
    void on_CoursespushButton_clicked();

    void on_CalculatepushButton_clicked();

    void on_PrintpushButton_clicked();

    void on_SavepushButton_clicked();

    void on_ClearpushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<LayoutWidgets> layoutArray;
    CUCP cucp;
    QString result{""};
    QString filePath;
    MainWindow *newWindow;


};


