#pragma once
// MyMouse.h
#include <queue>

class MyMouse;
class MouseEvent
{
public:
	enum class EventType
	{
		NullEvent,
		RClickDown,
		RClickUp,
		LClickDown,
		LClickUp,
		LClick,
		ScrollUp,
		ScrollDown,
		Move,
		Enter,
		Exit,
		RDoubleClick,
		LDoubleClick,
		SDoubleClick,
	};
public:
	MouseEvent() noexcept;
	MouseEvent(EventType xType, const MyMouse& parent) noexcept;
public:
	EventType GetEventType() const noexcept;
	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	bool CursorIsPressed() const noexcept;
	bool isNullEvent()const noexcept;
private:
	EventType eventType;
	bool leftIsPressed;
	bool rightIsPressed;
	bool cursorIsPressed;
	int xPos;
	int yPos;
	int scollDelta;
};

class MyMouse
{
public:
	MyMouse() = default;
public:
	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool GetRightPressed() const noexcept;
	bool GetLeftPressed() const noexcept;
	bool GetCursorPressed() const noexcept;
	bool GetIsInside() const noexcept;
	MouseEvent ReadEvent() noexcept;
	int ReadCursor() const noexcept;
	bool IsEmpty() const noexcept;
	void Flush() noexcept;
public:
	void RightPressSignal(int xXPos, int xYPos, int xState);
	void RightReleaseSignal(int xXPos, int xYPos, int xState);
	void LeftPressSignal(int xXPos, int xYPos, int xState);
	void LeftReleaseSignal(int xXPos, int xYPos, int xState);
	void ScrollPressSignal(int xXPos, int xYPos, int xState);
	void ScrollReleaseSignal(int xXPos, int xYPos, int xState);
	void MouseMoveSignal(int xXPos, int xYPos) noexcept;
	void CursorMoveSignal(int xDelta) noexcept;
	void MouseEnterSignal() noexcept;
	void MouseExitSignal() noexcept;
	void TrimBuffer() noexcept;
private:
	static constexpr unsigned int bufferSize = 16u;
	bool rightIsPressed = false;
	bool leftIsPressed = false;
	bool scrollIsPressed = false;
	bool isInside = false;
	int xPos;
	int yPos;
	int state;
	int ScrollDelta = 0;
	std::queue<MouseEvent> eventBuffer;
};