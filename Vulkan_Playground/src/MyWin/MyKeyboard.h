#pragma once
// MyKeyboard.h
#include <queue>
#include <bitset>


class Event
{
public:
	enum class EventType
	{
		Press, Rlease, Invalid
	};
public:
	Event();
	Event(EventType xType, unsigned char xCode);
	bool isPressed() const noexcept;
	bool isRelease() const noexcept;
	bool isValid() const noexcept;
	unsigned char GetCode() const noexcept;
private:
	EventType type;
	unsigned char code;
};


class MyKeyboard
{
public:
	MyKeyboard() = default;
public:
	// Key handling stuff
	bool KeyIsPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;
	// Char handling stuff
	char ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar()noexcept;
	void Flush()noexcept;
	// AutoRepeat Stuff
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnable() const noexcept;
public:
	void KeyPressSignal(unsigned char keycode) noexcept;
	void KeyReleaseSignal(unsigned char keycode) noexcept;
	void CharSignal(char character) noexcept;
	void ClearState() noexcept;
	static void TrimBuffer(std::queue<Event>& buffer)noexcept;
private:
	// Keyboard state stuffs
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<char> charBuffer;
	std::queue<Event> keyBuffer;
};