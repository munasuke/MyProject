#include "DxLib.h"
#include "CharactorObject.h"


CharactorObject::CharactorObject() :
	_flame(0),
	_currentCutIndex(0),
	gravity(1.0f)
{
	data.clear();
	cut.clear();
}


CharactorObject::~CharactorObject()
{
}

void CharactorObject::ChangeMode(std::string md)
{
	_flame = 0;
	_currentCutIndex = 0;
	mode = md;
}

void CharactorObject::Load(std::string filepath)
{
	FILE* file;
	fopen_s(&file, filepath.c_str(), "rb");
	fread(&header.version, sizeof(header.version), 1, file);

	fread(&header.filePathNameNum, sizeof(int), 1, file);

	header.pathName.resize(header.filePathNameNum);
	fread(&header.pathName[0], header.filePathNameNum, 1, file);

	fread(&header.actionDateNum, sizeof(int), 1, file);

	ImageDate dummy = {};
	for (int i = 0; i < header.actionDateNum; ++i) {
		fread(&dummy.actionNameNum, sizeof(dummy.actionNameNum), 1, file);

		dummy.actionName.resize(dummy.actionNameNum);
		fread(&dummy.actionName[0], dummy.actionNameNum, 1, file);

		fread(&dummy.loop, sizeof(dummy.loop), 1, file);

		fread(&dummy.count, sizeof(dummy.count), 1, file);

		data[i] = dummy;

		cut[dummy.actionName].resize(dummy.count);
		for (int j = 0; j < dummy.count; ++j) {
			fread(&cut[dummy.actionName][j], sizeof(cut[dummy.actionName][j]), 1, file);

			int num = 0;
			fread(&num, sizeof(int), 1, file);

			attackRect[dummy.actionName].resize(num);
			for (int k = 0; k < num; ++k) {
				fread(&attackRect[dummy.actionName][k], sizeof(attackRect[dummy.actionName][k]), 1, file);
			}
		}
	}
	fclose(file);
}

#ifdef _DEBUG
void CharactorObject::DrawRect()
{
	for (auto& a : attackRect[mode])
	{
		int tmpX = turnFlag ? pos.x - a.rect.Left() * 2 : pos.x + a.rect.Left() * 2;
		int tmpX2 = turnFlag ? pos.x - (a.rect.Left() + a.rect.Width()) * 2 : pos.x + (a.rect.Left() + a.rect.Width()) * 2;
		int color = a.type == RectType::attack ? 0xffff0000 : 0xff00ff00;
		DrawBox(tmpX, pos.y + a.rect.Top() * 2,
			tmpX2, pos.y + (a.rect.Top() + a.rect.Height()) * 2,
			color,
			false);
	}
}
#endif
bool CharactorObject::IsCollision(AttackRect rec1, AttackRect rec2)
{
	return false;
}
