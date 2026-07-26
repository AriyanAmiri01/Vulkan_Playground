// MyMouse.cpp
#include "MyMouse.h"


///////////////////////////////////////////////////////////////////
/// MOUSE EVENT STUFFS
MouseEvent::MouseEvent() noexcept
	:
	eventType(MouseEvent::EventType::NullEvent),
	leftIsPressed(false),
	rightIsPressed(false),
	xPos(0),
	yPos(0)
{
}
MouseEvent::MouseEvent(EventType xType, const MyMouse& parent) noexcept
	:
	eventType(xType),
	leftIsPressed(parent.GetLeftPressed()),
	rightIsPressed(parent.GetRightPressed()),
	xPos(parent.GetPosX()),
	yPos(parent.GetPosY())
{
}
bool MouseEvent::isNullEvent() const noexcept
{
	if(eventType == MouseEvent::EventType::NullEvent){
		return true;
	}
	else{
		return false;
	}
}
MouseEvent::EventType MouseEvent::GetEventType() const noexcept
{
	return eventType;
}
std::pair<int, int> MouseEvent::GetPos() const noexcept
{
	return std::pair<int, int>(xPos, yPos);
}
int MouseEvent::GetPosX() const noexcept
{
	return xPos;
}
int MouseEvent::GetPosY() const noexcept
{
	return yPos;
}
bool MouseEvent::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}
bool MouseEvent::RightIsPressed() const noexcept
{
	return rightIsPressed;
}
bool MouseEvent::CursorIsPressed() const noexcept
{
	return cursorIsPressed;
}


///////////////////////////////////////////////////////////////////
/// COMMUNCATION WITH OUTSIDE WORLD STUFF
void MyMouse::RightPressSignal(int xXPos, int xYPos, int xState)
{
	rightIsPressed = true;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::RClickDown, *this));
	TrimBuffer();
}
void MyMouse::RightReleaseSignal(int xXPos, int xYPos, int xState)
{
	rightIsPressed = false;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::RClickUp, *this));
	TrimBuffer();
}
void MyMouse::LeftPressSignal(int xXPos, int xYPos, int xState)
{
	leftIsPressed = true;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::LClickDown, *this));
	TrimBuffer();
}
void MyMouse::LeftReleaseSignal(int xXPos, int xYPos, int xState)
{
	leftIsPressed = false;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::LClickUp, *this));
	TrimBuffer();
}
void MyMouse::ScrollPressSignal(int xXPos, int xYPos, int xState)
{
	scrollIsPressed = true;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::ScrollDown, *this));
	TrimBuffer();
}
void MyMouse::ScrollReleaseSignal(int xXPos, int xYPos, int xState)
{
	scrollIsPressed = false;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::ScrollUp, *this));
	TrimBuffer();
}
void MyMouse::MouseMoveSignal(int xXPos, int xYPos) noexcept
{
	xPos = xXPos;
	yPos = xYPos;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, *this));
	TrimBuffer();
}
void MyMouse::CursorMoveSignal(int xDelta) noexcept
{
	ScrollDelta = xDelta;
}
void MyMouse::MouseEnterSignal() noexcept
{

	isInside = true;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::Enter, *this));
	TrimBuffer();
}
void MyMouse::MouseExitSignal() noexcept
{

	isInside = false;
	eventBuffer.push(MouseEvent(MouseEvent::EventType::Exit, *this));
	TrimBuffer();
}
void MyMouse::TrimBuffer() noexcept
{
	while(eventBuffer.size() > 16)
	{
		eventBuffer.pop();
	}
}


///////////////////////////////////////////////////////////////////
/// MYMOUSE HANDLING STUFFS
std::pair<int, int> MyMouse::GetPos() const noexcept
{
	return std::pair<int, int>(xPos, yPos);
}
int MyMouse::GetPosX() const noexcept
{
	return xPos;
}
int MyMouse::GetPosY() const noexcept
{
	return yPos;
}
bool MyMouse::GetRightPressed() const noexcept
{
	return rightIsPressed;
}
bool MyMouse::GetLeftPressed() const noexcept
{
	return leftIsPressed;
}
bool MyMouse::GetCursorPressed() const noexcept
{
	return false;
}
bool MyMouse::GetIsInside() const noexcept
{
	return isInside;
}
bool MyMouse::IsEmpty() const noexcept
{
	return false;
}
void MyMouse::Flush() noexcept
{
	eventBuffer = std::queue<MouseEvent>();
}
MouseEvent MyMouse::ReadEvent() noexcept
{
	if(eventBuffer.size() > 0u){
		MouseEvent e = eventBuffer.front();
		eventBuffer.pop();
		return e;
	}
	else{
		return MouseEvent();
	}
}
int MyMouse::ReadCursor() const noexcept
{
	return ScrollDelta;
}