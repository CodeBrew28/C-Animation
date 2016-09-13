
#ifndef COLOR_H
#define COLOR_H


class Color {
   public:
      Color();
      Color(double rInput, double gInput, double bInput);
      double getR() const;
      double getG() const;
      double getB() const;
      void setR(double rInput);
      void setG(double gInput);
      void setB(double bInput);
   private:
      double r;
      double g;
      double b;
};

#endif //Color.h