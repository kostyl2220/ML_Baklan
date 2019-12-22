#include "pch.h"
#include "Homa.h"

Action Homa::GetDesiredAction(ReceptorsState const& state)
{
	m_hit = false;
	if (state.blink)
	{
		return Action::PickUp;
	}

	if (state.wind)
	{
		if (m_movementDir == m_lookDir)
		{
			return Action::RotateRight;
		}
		else
		{
			RestoreDirection();
		}
	}

	if (state.smell && !state.cry && m_isArrowAvaliable)
	{
		if (m_homaPos.y != 0 || m_homaPos.y == 0 && m_homaPos.x == 0 || m_homaPos.y == 3)
		{
			if (m_actionSequence.size() >= 1)
			{
				return m_lookDir == LookDirection::RIGHT ?
					Action::Shoot :
					Action::RotateLeft;
			}

			return m_lookDir == LookDirection::DOWN ?
				Action::Shoot :
				m_lookDir == LookDirection::RIGHT ?
				Action::RotateRight :
				Action::RotateLeft;
		}

		if (!m_facedWiy)
		{
			m_facedWiy = true;
			m_movementDir = LookDirection::LEFT;
			m_actionSequence.push_back(LookDirection::RIGHT);
			m_actionSequence.push_back(LookDirection::UP);
			m_actionSequence.push_back(LookDirection::DOWN);
			return RestoreDirection();
		}
		else if (m_actionSequence.empty())
		{
			if (m_movementDir == m_lookDir)
			{
				return Action::Shoot;
			}
			return RestoreDirection();
		}
	}

	if (state.hit)
	{
		auto const rotateAction = m_lookDir == LookDirection::RIGHT ? Action::RotateRight : Action::RotateLeft;
		m_actionSequence.push_back(m_movementDir == LookDirection::RIGHT ? LookDirection::LEFT : LookDirection::RIGHT);
		m_movementDir = LookDirection::DOWN;
		return rotateAction;
	}

	if (m_movementDir == m_lookDir)
	{
		if (!m_actionSequence.empty())
		{
			m_movementDir = m_actionSequence.back();
			m_actionSequence.pop_back();
		}
		return Action::MoveUP;
	}
	return RestoreDirection();
}

Action Homa::RestoreDirection()
{
	int const curLookDir = (int)m_lookDir;
	int const desigredLookDir = (int)m_movementDir;
	if (curLookDir - desigredLookDir == 1 
		|| desigredLookDir - curLookDir == 3)
	{
		return Action::RotateLeft;
	}
	else if (desigredLookDir - curLookDir == 1
		|| curLookDir - desigredLookDir == 3)
	{
		return Action::RotateRight;
	}
	else return Action::RotateRight;
}