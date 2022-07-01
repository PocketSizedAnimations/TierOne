// Copyrighted - Pocket Sized Animations && Micah A. Parker - 2022


#include "Operators/SquadInfo.h"
#include "Operators/OperatorInfo.h"

ASquadInfo::ASquadInfo()
{
	/*replication*/
	bReplicates = true;
}




bool ASquadInfo::AddOperator(AOperatorInfo* Operator)
{
	Operators.Add(Operator);
	Operator->Squad = this;

	if (OnRosterChange.IsBound())
		OnRosterChange.Broadcast(this);

	if (OnOperatorAdded.IsBound())
		OnOperatorAdded.Broadcast();

	return true;
}

AOperatorInfo* ASquadInfo::GetOperator(uint8 Index)
{
	if (Operators.IsValidIndex(Index))
		return Operators[Index];

	else
		return nullptr;
}
