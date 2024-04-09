#include "RegulatorBB.h"

RegulatorBB::RegulatorBB()
{

}

RegulatorBB::~RegulatorBB()
{

}

float RegulatorBB::ustawWarPoprzednia(float _zadanaTemp, float _warPoprzednia)
{
	return 0;
}

float RegulatorBB::steruj(float _zadanaTemp, float _czasPomiedzy, float _warZmierzona)
{
	if (_zadanaTemp < _warZmierzona)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}