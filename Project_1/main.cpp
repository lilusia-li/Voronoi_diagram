#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath> 
#define PI 3.14159265 


using namespace std;

struct Point
{
    double x;
    double y;

    Point() {};
    ~Point() {};
    Point(double xx, double yy)
    {
        x = xx;
        y = yy;
    }
};

struct Line //y = kx + b - ��������� ������
{
    double k;
    double b;

    //��� �������, ����� ������ ����������� ����� �� ����
    double x;
    double y;

    Line(double kk, double bb)
    {
        k = kk;
        b = bb;
        x = 0;
        y = 0;
    }
    Line() //����������� �� ���������
    {
        k = 0;
        b = 0;
        x = 0;
        y = 0;
    }
    ~Line() {};
};

bool operator == (const Line& a, const Line& b)
{
    if (a.x == b.x && a.y == b.y && a.k == b.k && a.b == b.b)
        return true;
    return false;
}

bool operator < (const Point& a, const Point& b)
{
    if (a.y != b.y)
        return a.y < b.y;
    return a.x < b.x;
}

void medianPerpendicularsForSite(Point point, vector <Point> points, vector <Line>* medianPerpendiculars)
{
    //��������� (n-1) ���������� ��������������� ��� ������� �����
    for (int j = 0; j < points.size(); j++)
    {
        if (points[j].x != point.x || points[j].y != point.y)
        {
            Point M; //�������� �������, ������������ ��������������� �����
            M.x = (point.x + points[j].x) / 2;
            M.y = (point.y + points[j].y) / 2;

            Line AB; //������, ����������� �����
            if (point.x != points[j].x && point.y != points[j].y)
            {
                AB.k = (point.y - points[j].y) / (point.x - points[j].x);
                //AB.b = (points[i].y * points[j].x - points[j].y * points[i].x) / (points[j].x - points[i].x);

                Line perpendicular;
                perpendicular.k = -1 / AB.k;
                perpendicular.b = M.y + M.x / AB.k;

                (*medianPerpendiculars).push_back(perpendicular);
            }
            else
            {
                if (point.x == points[j].x)
                {
                    AB.x = point.x; //������ �������, ����������� ���� � ��������������� ����� - ����������� OY, x = AB.x
                    //� ������ ����� || OX
                    Line perpendicular;
                    perpendicular.k = 0;
                    perpendicular.b = 0;
                    perpendicular.y = M.y;

                    (*medianPerpendiculars).push_back(perpendicular);
                }
                else
                {
                    AB.y = point.y; //������ �������, ����������� ���� � ��������������� ����� - ����������� OX, y = AB.y
                    //� ������ ����� || OY
                    Line perpendicular;
                    perpendicular.k = 0;
                    perpendicular.b = 0;
                    perpendicular.x = M.x;

                    (*medianPerpendiculars).push_back(perpendicular);
                }
            }
        }
    }
    Line line;
    line.x = 10;
    line.y = 10;
    (*medianPerpendiculars).push_back(line); //��������� �� ���� ����� ��� ����� - ����������� ������ ���� �� � � �� Y

    (*medianPerpendiculars).push_back(Line()); //��������� �� ���� ����� ��� ����� - ��� ���������
}

void removeRepetitions(vector <Point>* vec)
{
    //������� ������������� ����� (��� ��������� ������� � ���� ���������� ������������ �����)

    for (int i = 0; i < (*vec).size() - 1; i++)
    {
        for (int j = i + 1; j < (*vec).size(); j++)
        {
            if ((*vec)[i].x == (*vec)[j].x &&
                (*vec)[i].y == (*vec)[j].y && i != j)
            {
                auto it = (*vec).begin() + j;
                (*vec).erase(it);
                j -= 1;
            }
        }
    }
}

void intersectionsPerpendicularsForSite(const vector <Line>* const medianPerpendiculars, vector <Point>* intersectionsPerpendiculars)
{
    //Line two(-3, 15);

    //��������� ����� ����������� ���������� ��������������� ����� ����� � � ����� ���������
    for (int k = 0; k < (*medianPerpendiculars).size() - 1; k++)
    {
        for (int f = k + 1; f < (*medianPerpendiculars).size(); f++)
        {
            if (((*medianPerpendiculars)[k].k != (*medianPerpendiculars)[f].k) ||
            (
                ((*medianPerpendiculars)[k].k == 0) && ((*medianPerpendiculars)[f].k == 0) &&
                (
                    (
                    (*medianPerpendiculars)[k].x == 0 && (*medianPerpendiculars)[f].x != 0 ||
                    (*medianPerpendiculars)[k].y == 0 && (*medianPerpendiculars)[f].y != 0 ||
                    (*medianPerpendiculars)[f].x == 0 && (*medianPerpendiculars)[k].x != 0 ||
                    (*medianPerpendiculars)[f].y == 0 && (*medianPerpendiculars)[k].y != 0
                    )
                )
            )
                )
                //������ ������ ������������ (������� �������������� ������)
            {
                if ((*medianPerpendiculars)[f].x == 0 && (*medianPerpendiculars)[f].y == 0 && (*medianPerpendiculars)[f].k == 0 && (*medianPerpendiculars)[f].b == 0)
                {
                    if ((*medianPerpendiculars)[k].x != 0) //������ �� ������ ��������� ����������� ������, ������������ OY � �����
                    {
                        Point intersection; //����� (x, 0)
                        intersection.x = (*medianPerpendiculars)[k].x;
                        intersection.y = 0;
                        if (intersection.x >= 0 && intersection.y >= 0)
                            (*intersectionsPerpendiculars).push_back(intersection);

                        //��� ��������, � ������� � � � � - �� 0
                        if ((*medianPerpendiculars)[k].y != 0) //������ �� ������ ��������� ����������� ������, ������������ O� � �����
                        {
                            //����� (0, y)
                            intersection.x = 0;
                            intersection.y = (*medianPerpendiculars)[k].y;
                            if (intersection.x >= 0 && intersection.y >= 0)
                                (*intersectionsPerpendiculars).push_back(intersection);
                        }
                    }
                    else
                    {
                        if ((*medianPerpendiculars)[k].y != 0) //������ �� ������ ��������� ����������� ������, ������������ O� � �����
                        {
                            Point intersection; //����� (0, y)
                            intersection.x = 0;
                            intersection.y = (*medianPerpendiculars)[k].y;
                            if (intersection.x >= 0 && intersection.y >= 0)
                                (*intersectionsPerpendiculars).push_back(intersection);
                        }
                        else //������ �� ������ ��������� ����������� ������� ������, �� ������������ ����, � �����
                        {
                            if ((*medianPerpendiculars)[k].b == 0)
                                (*intersectionsPerpendiculars).push_back(Point(0, 0)); //����� (0, 0)
                            else
                            {
                                Point intersection; //����� (0, y)
                                intersection.x = 0;
                                intersection.y = (*medianPerpendiculars)[k].b;
                                if (intersection.x >= 0 && intersection.y >= 0)
                                    (*intersectionsPerpendiculars).push_back(intersection);

                                //����� (x, 0)
                                intersection.x = -(*medianPerpendiculars)[k].b / (*medianPerpendiculars)[k].k;
                                intersection.y = 0;
                                if (intersection.x >= 0 && intersection.y >= 0)
                                    (*intersectionsPerpendiculars).push_back(intersection);
                            }
                        }
                    }
                }
                else //������ ��� ������ - �� ���
                {
                    if ((*medianPerpendiculars)[k].x != 0) //������ �� ������ ��������� ����������� ������, ������������ OY
                    {
                        if ((*medianPerpendiculars)[k].y != 0) //��� �������� � ������� x � y �� 0
                        {
                            //� ������� ������, �� ������������ ����
                            Point intersection; //����� (x, ?)
                            intersection.x = (*medianPerpendiculars)[k].x;
                            intersection.y = (*medianPerpendiculars)[f].k * (*medianPerpendiculars)[k].x + (*medianPerpendiculars)[f].b;
                            if (intersection.x >= 0 && intersection.y >= 0)
                                (*intersectionsPerpendiculars).push_back(intersection);

                            //����� (?, y)
                            intersection.x = ((*medianPerpendiculars)[k].y - (*medianPerpendiculars)[f].b) / (*medianPerpendiculars)[f].k;
                            intersection.y = (*medianPerpendiculars)[k].y;
                            if (intersection.x >= 0 && intersection.y >= 0)
                                (*intersectionsPerpendiculars).push_back(intersection);
                        }
                        else
                        {
                            if ((*medianPerpendiculars)[f].y != 0) //� ������, ������������ O�
                            {
                                Point intersection; //����� (x, y)
                                intersection.x = (*medianPerpendiculars)[k].x;
                                intersection.y = (*medianPerpendiculars)[f].y;
                                if (intersection.x >= 0 && intersection.y >= 0)
                                    (*intersectionsPerpendiculars).push_back(intersection);
                            }
                            else //� ������� ������, �� ������������ ����
                            {
                                Point intersection; //����� (x, ?)
                                intersection.x = (*medianPerpendiculars)[k].x;
                                intersection.y = (*medianPerpendiculars)[f].k * (*medianPerpendiculars)[k].x + (*medianPerpendiculars)[f].b;
                                if (intersection.x >= 0 && intersection.y >= 0)
                                    (*intersectionsPerpendiculars).push_back(intersection);
                            }
                        }
                    }
                    else
                    {
                        if ((*medianPerpendiculars)[k].y != 0) //������ �� ������ ��������� ����������� ������, ������������ O�
                        {
                            if ((*medianPerpendiculars)[f].x != 0) //� ������, ������������ OY
                            {
                                Point intersection; //����� (x, y)
                                intersection.x = (*medianPerpendiculars)[f].x;
                                intersection.y = (*medianPerpendiculars)[k].y;
                                if (intersection.x >= 0 && intersection.y >= 0)
                                    (*intersectionsPerpendiculars).push_back(intersection);
                            }
                            else //� ������� ������, �� ������������ ����
                            {
                                Point intersection; //����� (?, y)
                                intersection.x = ((*medianPerpendiculars)[k].y - (*medianPerpendiculars)[f].b) / (*medianPerpendiculars)[f].k;
                                intersection.y = (*medianPerpendiculars)[k].y;
                                if (intersection.x >= 0 && intersection.y >= 0)
                                    (*intersectionsPerpendiculars).push_back(intersection);
                            }
                        }
                        else //������ �� ������ ��������� ����������� ������� ������, �� ������������ ����
                        {
                            if ((*medianPerpendiculars)[f].x != 0) //C ������, ������������ OY
                            {
                                Point intersection; //����� (x, ?)
                                intersection.x = (*medianPerpendiculars)[f].x;
                                intersection.y = (*medianPerpendiculars)[k].k * (*medianPerpendiculars)[f].x + (*medianPerpendiculars)[k].b;
                                if (intersection.x >= 0 && intersection.y >= 0)
                                    (*intersectionsPerpendiculars).push_back(intersection);

                                //��� �������, ����� x != 0 � y != 0
                                if ((*medianPerpendiculars)[f].y != 0) //� ������, ������������ O�
                                {
                                    //����� (?, y)
                                    intersection.x = ((*medianPerpendiculars)[f].y - (*medianPerpendiculars)[k].b) / (*medianPerpendiculars)[k].k;
                                    intersection.y = (*medianPerpendiculars)[f].y;
                                    if (intersection.x >= 0 && intersection.y >= 0)
                                        (*intersectionsPerpendiculars).push_back(intersection);
                                }
                            }
                            else
                            {
                                if ((*medianPerpendiculars)[f].y != 0) //� ������, ������������ O�
                                {
                                    Point intersection; //����� (?, y)
                                    intersection.x = ((*medianPerpendiculars)[f].y - (*medianPerpendiculars)[k].b) / (*medianPerpendiculars)[k].k;
                                    intersection.y = (*medianPerpendiculars)[f].y;
                                    if (intersection.x >= 0 && intersection.y >= 0)
                                        (*intersectionsPerpendiculars).push_back(intersection);
                                }
                                else //� ������� ������, �� ������������ ����
                                {
                                    //����� (?, ?)
                                    Point intersection;
                                    intersection.x = ((*medianPerpendiculars)[k].b - (*medianPerpendiculars)[f].b) / ((*medianPerpendiculars)[f].k - (*medianPerpendiculars)[k].k);
                                    intersection.y = intersection.x * (*medianPerpendiculars)[k].k + (*medianPerpendiculars)[k].b;
                                    if (intersection.x >= 0 && intersection.y >= 0)
                                        (*intersectionsPerpendiculars).push_back(intersection);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    (*intersectionsPerpendiculars).push_back(Point(0, 0)); //��������� ����� �������� ���������
    (*intersectionsPerpendiculars).push_back(Point(10, 10)); //��������� ����� ����������� �������������� ������

    //������� ������������� ����� (��� ��������� ������� � ���� ���������� ������������ �����)
    removeRepetitions(intersectionsPerpendiculars);
    removeRepetitions(intersectionsPerpendiculars);
}



void pointsForLocusOfSite(const vector <Line>* const medianPerpendiculars, const vector <Point>* const intersectionsPerpendiculars,
                            vector <Point>* const pointsForLocus, Point point)
{
    //�������� ����� �� �������������� ���� �������������� - ��� ��������� ����� ��� ������
    bool flag = false;

    for (int f = 0; f < (*intersectionsPerpendiculars).size(); f++) //��������� ������ �����, �� ���� �� ��� ������� � ������� ������
    {
        for (int j = 0; j < (*medianPerpendiculars).size() - 1; j++) //�� ��������� ��� ���������
        {
            if ((*medianPerpendiculars)[j].x != 0) //������ ������ || OY
            {
                if ((point.x <= (*medianPerpendiculars)[j].x && (*intersectionsPerpendiculars)[f].x > (*medianPerpendiculars)[j].x) ||
                    (point.x >= (*medianPerpendiculars)[j].x && (*intersectionsPerpendiculars)[f].x < (*medianPerpendiculars)[j].x))
                {
                    flag = true;
                    break;
                }
                //��� ��������, � ������� � � � � - �� 0
                if ((*medianPerpendiculars)[j].y != 0) //������ ������ || OX
                {
                    if ((point.y <= (*medianPerpendiculars)[j].y && (*intersectionsPerpendiculars)[f].y > (*medianPerpendiculars)[j].y) ||
                        (point.y >= (*medianPerpendiculars)[j].y && (*intersectionsPerpendiculars)[f].y < (*medianPerpendiculars)[j].y))
                    {
                        flag = true;
                        break;
                    }
                }
            }
            else
            {
                if ((*medianPerpendiculars)[j].y != 0) //������ ������ || OX
                {
                    if ((point.y <= (*medianPerpendiculars)[j].y && (*intersectionsPerpendiculars)[f].y > (*medianPerpendiculars)[j].y) ||
                        (point.y >= (*medianPerpendiculars)[j].y && (*intersectionsPerpendiculars)[f].y < (*medianPerpendiculars)[j].y))
                    {
                        flag = true;
                        break;
                    }
                }
                else //������ ������� ������, �� ������������ ����
                {
                    double a = (*medianPerpendiculars)[j].k * point.x - point.y + (*medianPerpendiculars)[j].b;
                    double b = (*medianPerpendiculars)[j].k * (*intersectionsPerpendiculars)[f].x - (*intersectionsPerpendiculars)[f].y + (*medianPerpendiculars)[j].b;
                    if ((a >= 0 && b < -0.01) || (a <= 0 && b > 0.01))
                    {
                        flag = true;
                        break;
                    }
                }
            }
        }
        if (!flag)
        {
            (*pointsForLocus).push_back((*intersectionsPerpendiculars)[f]);
        }
        flag = false;
    }
}

void sort(vector <Point>* const pointsForLocus, Point point)
{
    vector <pair <double, Point>> vec;

    for (int j = 0; j < (*pointsForLocus).size(); j++)
    {
        double degree;
        Line AB; //������, ����������� �����
        if (point.x != (*pointsForLocus)[j].x && point.y != (*pointsForLocus)[j].y)
        {
            AB.k = (point.y - (*pointsForLocus)[j].y) / (point.x - (*pointsForLocus)[j].x);

            degree = (atan(AB.k) * 180 / PI); //�� -90 �� 90 ��������

            //������ ���������� ���������� ��������

            if (degree > 0) //������ ������ �� �� 0 �� 90 ��������
            {
                if (point.x > (*pointsForLocus)[j].x) //������ ����� � ���� ��������� 180 ��������
                {
                    degree += 180;
                }
            }
            else //������ ������ �� �� -90 �� 0 ��������
            {
                if (point.x > (*pointsForLocus)[j].x) //������ ����� � ���� ��������� 180 ��������
                {
                    degree += 180;
                }
            }
            //� ����� ��� ���� ����� �� -90 �� 270 ��������
        }
        else
        {
            if (point.x == (*pointsForLocus)[j].x)
            {
                AB.x = point.x; //������ �������, ����������� ���� � ��������������� ����� - ����������� OY, x = AB.x
                if (point.y > (*pointsForLocus)[j].y)
                    degree = 270;
                else
                    degree = 90;
            }
            else
            {
                AB.y = point.y; //������ �������, ����������� ���� � ��������������� ����� - ����������� OX, y = AB.y
                if (point.x > (*pointsForLocus)[j].x)
                    degree = 180;
                else
                    degree = 0;
            }
        }
        vec.push_back(make_pair(degree, (*pointsForLocus)[j]));
    }
    (*pointsForLocus).clear();

    sort(vec.begin(), vec.end());

    for (auto p : vec)
    {
        (*pointsForLocus).push_back(p.second);
    }
}

vector <vector <Point>> determineLocuses(vector <Point> points)
{
    vector <Line> medianPerpendiculars;
    vector <Point> intersectionsPerpendiculars;
    vector <Point> pointsForLocus;

    vector <vector <Point>> locuses;

    for (int i = 0; i < points.size(); i++)
    {
        //��������� (n-1) ���������� ��������������� ��� ������� �����
        medianPerpendicularsForSite(points[i], points, &medianPerpendiculars);
        
        //��������� ����� ����������� ���������� ��������������� ����� ����� � � ����� ���������
        intersectionsPerpendicularsForSite(&medianPerpendiculars, &intersectionsPerpendiculars);

        //������ � ��� ���� ��� ����� ����������� ���������� ��������������� � ������� intersectionsPerpendiculars
        //���� points[i]
        //�������� ����� �� �������������� ���� �������������� - ��� ��������� ����� ��� ������
        pointsForLocusOfSite(&medianPerpendiculars, &intersectionsPerpendiculars, &pointsForLocus, points[i]);

        //������� ���������� ����� ��� ������, � ������ ��� ���������� ������ �������
        sort(&pointsForLocus, points[i]);


        //��������� ������ ����� ������, �������� � ����������, � ����� ������ �������
        locuses.push_back(pointsForLocus);

        medianPerpendiculars.clear();
        intersectionsPerpendiculars.clear();
        pointsForLocus.clear();
    }
    return locuses;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(3);
    int n = rand() % 10 + 2; //���������� �������� ����� (������)
    
    vector <Point> points;

    for (int i = 0; i < n; i++)
    {
        double x = rand() % 9 + 1, y = rand() % 9 + 1;
        points.push_back(Point(x, y));
    }

    removeRepetitions(&points);
    n = points.size();

    cout << "������� ���������������� �����" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << points[i].x << " " << points[i].y << endl;
    }

    vector <vector <Point>> locuses = determineLocuses(points);
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Diagram");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        sf::ConvexShape conv;

        int r = 25, g = 20, b = 30;

        for (int i = 0; i < locuses.size(); i++)
        {
            // resize it to i points
            conv.setPointCount(locuses[i].size());

            // define the points
            for (int j = 0; j < locuses[i].size(); j++)
            {
                conv.setPoint(j, sf::Vector2f(locuses[i][j].x * 100, locuses[i][j].y * 100));
            }

            // set the color
            conv.setFillColor(sf::Color(r, g, b));

            window.draw(conv);
            r += 15;
            g += 10;
            b += 10;
        }
        // define a circle with radius = 5
        sf::CircleShape circle(5.f);

        for (int i = 0; i < points.size(); i++)
        {
            circle.setPosition(points[i].x * 100, points[i].y * 100);

            circle.setFillColor(sf::Color::White);

            window.draw(circle);
        }

        window.display();
    }

}