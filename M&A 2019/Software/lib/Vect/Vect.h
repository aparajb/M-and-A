	#ifndef VECTOR_H_
#define VECTOR_H_

#include <Common.h>

class Vect{
	public:
		Vect();
		Vect(float val1, float val2, bool isPolar = true);
		void setStandard(float _i, float _j);
		void setPolar(float _mag, float _arg);
		
		Vect operator+(Vect vector2);
		Vect operator-(Vect vector2);
		Vect operator*(float scalar);
		Vect operator/(float scalar);
		void operator+=(Vect vector2);
		void operator-=(Vect vector2);
		Vect operator*=(float scalar);
		Vect operator/=(float scalar);

		bool operator==(Vect vector2);
		bool operator!=(Vect vector2);
		bool operator<(Vect vector2);
		bool operator<=(Vect vector2);
		bool operator>(Vect vector2);
		bool operator>=(Vect vector2);

		bool exists();
		bool isBetween(float leftAngle, float rightAngle);

		float i, j, mag, arg;
		
	private:
		float calcI(float _mag, float _arg);
		float calcJ(float _mag, float _arg);

		float calcMag(float _i, float _j);
		float calcArg(float _i, float _j);
};

#endif