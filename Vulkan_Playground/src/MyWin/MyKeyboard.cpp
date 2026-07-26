// MyKeyboard.cpp
#include "MyKeyboard.h"


////////////////////////////////////////////////////////////////////
///	EVENT STUFFS
Event::Event()
	:
	type(EventType::Invalid),
	code(0u)
{
}
Event::Event(EventType xType, unsigned char xCode)
	:
	type(xType),
	code(xCode)
{
}
bool Event::isPressed() const noexcept
{
	return type == EventType::Press;
}
bool Event::isRelease() const noexcept
{
	return type == EventType::Rlease;
}
bool Event::isValid() const noexcept
{
	return type != EventType::Invalid;
}
unsigned char Event::GetCode() const noexcept
{
	return code;
}


////////////////////////////////////////////////////////////////////
///	KEY STUFFS
bool MyKeyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}
Event MyKeyboard::ReadKey() noexcept
{
	if(keyBuffer.size() > 0u) {
		Event e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
	else {
		return Event();
	}
}
bool MyKeyboard::KeyIsEmpty() const noexcept
{
	return keyBuffer.empty();
}
void MyKeyboard::FlushKey() noexcept
{
	keyBuffer = std::queue<Event>();
}


////////////////////////////////////////////////////////////////////
///	CHAR KEYBOARD STUFF
char MyKeyboard::ReadChar() noexcept
{
	if(charBuffer.size() > 0u) {
		unsigned char charcode = charBuffer.front();
		charBuffer.pop();
		return charcode;
	}
	else
	{
		return 0;
	}
}
bool MyKeyboard::CharIsEmpty() const noexcept
{
	return charBuffer.empty();
}
void MyKeyboard::FlushChar() noexcept
{
	charBuffer = std::queue<char>();
}
void MyKeyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}


////////////////////////////////////////////////////////////////////
///	AUTO CLICK STUFFS
void MyKeyboard::EnableAutorepeat()noexcept {
	autorepeatEnabled = true;
}
void MyKeyboard::DisableAutorepeat()noexcept
{
	autorepeatEnabled = false;
}
bool MyKeyboard::AutorepeatIsEnable() const noexcept
{
	return autorepeatEnabled;
}


////////////////////////////////////////////////////////////////////
///	EXTERNAL COMMUNICATION STUFFS
void MyKeyboard::KeyPressSignal(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keyBuffer.push(Event(Event::EventType::Press, keycode));
	TrimBuffer(keyBuffer);
}
void MyKeyboard::KeyReleaseSignal(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keyBuffer.push(Event(Event::EventType::Rlease, keycode));
	TrimBuffer(keyBuffer);
}
void MyKeyboard::CharSignal(char character) noexcept
{
	charBuffer.push(character);
	TrimBuffer(keyBuffer);
}
void MyKeyboard::ClearState() noexcept
{
	keystates.reset();
}
void MyKeyboard::TrimBuffer(std::queue<Event>& buffer) noexcept
{
	while(buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}