#pragma once
#include "CImageObject.h"
class CGround :  public CImageObject
{
public:
	CGround();
	virtual ~CGround();

private:
	CImage* m_pImage;

public:
	CImage* GetIamge();
	void SetImage(CImage* pImage);

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

