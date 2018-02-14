#include <QtWidgets>
#include <QtCharts>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace QtCharts;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineSeries *series = new QLineSeries();

    std::string str;
    std::ifstream myfile ("Prime.txt");

    int i;
    int j;
    if (myfile.is_open())
    {
      while (myfile >> str)
      {
        std::istringstream buffer1(str);
        buffer1 >> i;
        myfile >> str;
        std::istringstream buffer2(str);
        buffer2 >> j;
        series->append(i, j);
      }
      myfile.close();
    }

    else std::cout << "Unable to open file";

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    //chart->createDefaultAxes();

    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(5);
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTickCount(7);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();

    return 0;
}
