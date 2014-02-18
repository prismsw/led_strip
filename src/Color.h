class Color {
private:
    int r;
    int g;
    int b;

    double h;
    double s;
    double v;

    int boundedRGB(int);
    void updateHSV();
    void updateRGB();
public:
    Color(int, int, int);

    // RGB functions
    int getR();
    int getG();
    int getB();

    void setR(int);
    void setG(int);
    void setB(int);

    void incR(int);
    void incG(int);
    void incB(int);

    // HSV functions
    double getH();
    double getS();
    double getV();

    void setH(double);
    void setS(double);
    void setV(double);

    void incH(double);
    void incS(double);
    void incV(double);
};

