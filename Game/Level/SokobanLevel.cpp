#include "SokobanLevel.h"

#include <iostream>
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

#include <Windows.h>
#include "Engine.h"


SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map.txt");
}

void SokobanLevel::ReadMapFile(const char* _fileName)
{
	// ���� ���� ��� �ϼ�
	char filePath[256] = { };
	sprintf_s(filePath, 256, "../Assets/%s", _fileName);

	FILE* file = nullptr;
	fopen_s(&file, filePath, "rb");

	// ����ó��
	if (nullptr == file)
	{
		std::cout << "�� ���� �б� ����." << _fileName << "\n";
		__debugbreak();
		return;
	}

	// �Ľ�(Parcing, �ؼ�)
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// ���� ũ��� �о���� ũ�Ⱑ �ٸ� ���
	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize\n";
	}

	// �迭 ��ȸ�� ���� �ε��� ����
	int index = 0;

	// ���ڿ� ���� ��
	int size = (int)readSize;
	
	// x, y ��ǥ
	Vector2 position;

	//���� �迭 ��ȸ
	while (index < size)
	{
		// �� ���� Ȯ��
		char mapCharacter = buffer[index++];

		// ���� ���� ó��
		if (mapCharacter == '\n')
		{
			// ���� �ٷ� �ѱ�鼭, x ��ǥ �ʱ�ȭ
			++position.y;
			position.x = 0;

			// @Todo: �׽�Ʈ�뵵. ���߿� �����ؾ���.
			std::cout << "\n";
			continue;
		}

		//�� ���� ó��
		switch (mapCharacter)
		{
		case '#':	// ��
			AddActor(new Wall(position));
			break;
		case '.':	// �ٴ�
			AddActor(new Ground(position));
			break;
		case 'p':	// �÷��̾�
			AddActor(new Ground(position));
			AddActor(new Player(position));
			break;
		case 'b':	// �ڽ�
			AddActor(new Ground(position));
			AddActor(new Box(position));
			break;
		case 't':	// Ÿ��
			AddActor(new Target(position));
			break;
		}

		// x ��ǥ ���� ó��
		++position.x;
	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);
}
