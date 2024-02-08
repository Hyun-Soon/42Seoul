#include "Point.hpp"

Fixed	getRotDir(Point const a, Point const b, Point const point)
{
	const Fixed	aPos[2] = {a.getX(), a.getY()};
	const Fixed	bPos[2] = {b.getX(), b.getY()};
	const Fixed	pPos[2] = {point.getX(), point.getY()};

	Fixed	aDir[2] = {aPos[0] - bPos[0], aPos[1] - bPos[1]};
	Fixed	pDir[2] = {pPos[0] - bPos[0], pPos[1] - bPos[1]};

	//std::cout << "aDir : " << aDir[0] << ", " << aDir[1]
	//			<< "\npDir : " << pDir[0] << ", " << pDir[1] << "\n" << std::endl;
	
	Fixed	zDir(aDir[0] * pDir[1] - pDir[0] * aDir[1]);
	return (zDir);
}

bool bsp( Point const a, Point const b, Point const c, Point const point)
{
	Fixed	firstRet = getRotDir(a, b, point);
	Fixed	secondRet = getRotDir(b, c, point);
	Fixed	thirdRet = getRotDir(c, a, point);

	//std::cout << "a : " << firstRet
	//			<<"\nb : " << secondRet
	//			<<"\nc : " << thirdRet << std::endl;
	if ((firstRet > 0 && secondRet > 0 && thirdRet > 0)
		|| (firstRet < 0 && secondRet < 0 && thirdRet < 0))
		return (true);
	else
		return (false);
}

