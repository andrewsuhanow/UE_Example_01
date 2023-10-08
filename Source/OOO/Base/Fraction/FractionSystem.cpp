

//#include "../TEST_Fraction/FractionSystem.h"
#include "FractionSystem.h"


FFractionUnit::FFractionUnit(uint8 A, uint8 B, EUnitAttitudeStatus _Attitude) : 
							GroupSubjectA(A), GroupSubjectB(B), Attitude(_Attitude)
{}



// ** Correcting Fraction Massive
void UFractionSystem::Init(TArray<FFractionUnit>& _FractionsAttitude)
{

	// ** if duplicate element =>> DELETE it
	for (int32 i = 0; i < _FractionsAttitude.Num(); ++i)
	{
		for (int32 j = i+1; j < _FractionsAttitude.Num(); ++j)
		{
			if (_FractionsAttitude[i].GroupSubjectA == _FractionsAttitude[j].GroupSubjectA &&
				_FractionsAttitude[i].GroupSubjectB == _FractionsAttitude[j].GroupSubjectB)
			{
				_FractionsAttitude.RemoveAt(j);
				--j;
				continue;
			}
		}
	}

	// ** chack and add inverse element 
	for (int32 i = 0; i < _FractionsAttitude.Num(); ++i)
	{
		bool InverseElementExist = false;
		for (int32 j = i+1; j < _FractionsAttitude.Num(); ++j)
		{
			if (_FractionsAttitude[i].GroupSubjectA == _FractionsAttitude[j].GroupSubjectB &&
				_FractionsAttitude[i].GroupSubjectB == _FractionsAttitude[j].GroupSubjectA)
			{

				InverseElementExist = true;

				if (i+1 != j)
				{
					_FractionsAttitude.Swap(i+1, j);
				}
				++i;
				break;
			}
		}
		// ** Add new inverse
		if (!InverseElementExist)
		{
			FFractionUnit NewElement(_FractionsAttitude[i].GroupSubjectB, 
				_FractionsAttitude[i].GroupSubjectA, _FractionsAttitude[i].Attitude);
			//_FractionsAttitude.Add(NewElement);
			_FractionsAttitude.Insert(NewElement, i);
			++i;
		}
	}
}

EUnitAttitudeStatus UFractionSystem::GetAttitude(TArray<FFractionUnit>& _FractionsAttitude, 
																			uint8 A, uint8 B)
{ 
	if(A == B)
		return EUnitAttitudeStatus::Friend;

	for (int32 i = 0; i < _FractionsAttitude.Num(); ++i)
	{
		if (_FractionsAttitude[i].GroupSubjectA == A &&	_FractionsAttitude[i].GroupSubjectB == B)
		{
			return _FractionsAttitude[i].Attitude;
		}
	}

	return EUnitAttitudeStatus::Neutral; 
}


void UFractionSystem::U_LogFraction()
{

}