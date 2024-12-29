#pragma once

#include "mf_define.h"
#include "json11.h"

#include <string>
#include <vector>

//class MFItemBase {
//public:
//	MFItemBase(unsigned long id) : id_(id){}
//	virtual ~MFItemBase() {}
//
//	unsigned long id_;
//	virtual int GetName(char *name, int size) const = 0;
//	virtual int Test(const json11::Json& config, json11::Json& storage, std::string& result) const = 0;
//	virtual int Config(json11::Json& config) const {
//		return MFERR_NOERR;
//	}
//
//};

// MFItemBase Ŭ����: �˻� �׸��� �⺻ Ŭ������ �����մϴ�.
// �� Ŭ������ �ٸ� �˻� �׸� Ŭ�������� ��ӹ޾� ������ �������̽��� �����մϴ�.
class MFItemBase {
public:
    // ������: ��ü�� ������ �� �˻� �׸� ID�� �ʱ�ȭ�մϴ�.
    // id: �˻� �׸��� �ĺ��ϴ� ���� ID.
    MFItemBase(unsigned long id) : id_(id) {}

    // �Ҹ���: ��ü�� �Ҹ�� �� ȣ��˴ϴ�.
    // ���� �Ҹ��ڸ� ����Ͽ� ��ӹ��� Ŭ������ �ڿ��� �ùٸ��� �����ǵ��� �����մϴ�.
    virtual ~MFItemBase() {}

    // �˻� �׸� ID�� �����ϴ� ��� �����Դϴ�.
    unsigned long id_;

    // GetName �Լ�: �˻� �׸��� �̸��� �����ɴϴ�.
    // �� �Լ��� ���� ���� �Լ���, ��ӹ��� Ŭ�������� �ݵ�� �����ؾ� �մϴ�.
    // name: �˻� �׸��� �̸��� ������ ����.
    // size: ������ ũ��.
    // ��ȯ��: �Լ� ȣ�� ���� ���θ� ��Ÿ���� ���� ��.
    virtual int GetName(char* name, int size) const = 0;

    // Test �Լ�: �־��� ����(config)�� ������� �˻� �۾��� �����մϴ�.
    // config: �˻� ������ �����ϴ� JSON ��ü.
    // storage: �˻� ��� �����͸� ������ JSON ��ü.
    // result: �˻� ����� ���ڿ��� ������ ����.
    // ��ȯ��: �˻� ��� ���¸� ��Ÿ���� ���� ��.
    virtual int Test(const json11::Json& config, json11::Json& storage, std::string& result) const = 0;

    // Config �Լ�: �˻� �׸��� ����(config)�� ��ȯ�մϴ�.
    // �� �Լ��� �⺻������ �ƹ� �۾��� ���� ������ ��ӹ��� Ŭ�������� �ʿ信 ���� �������� �� �ֽ��ϴ�.
    // config: ���� �����͸� ������ JSON ��ü.
    // ��ȯ��: �Լ� ȣ�� ���� ���θ� ��Ÿ���� ���� ��.
    virtual int Config(json11::Json& config) const {
        // �⺻ ��ȯ������ ������ ������ ��Ÿ���ϴ�.
        return MFERR_NOERR;
    }
};


//class MFBase
//{
//public:
//	MFBase();
//	~MFBase();
//
//	virtual int Init(void) = 0;
//	virtual int Deinit(void) = 0;
//	virtual unsigned long GetLibId(void) = 0;
//	virtual int GetLibName(char* id, int len) = 0;
//	virtual const std::string GetVersion(void) const = 0;
//
//	virtual int Config(json11::Json& config) {
//		return MFERR_NOERR;
//	}
//	virtual int PreTest(void) {
//		return MFERR_NOERR;
//	}
//	virtual int PostTest(void) {
//		return MFERR_NOERR;
//	}
//	virtual int MessageCallback(WPARAM wp, LPARAM lp) {
//		return MFERR_NOERR;
//	}
//
//	void(*PrintLog)(const char *fmt, ...);
//
//	std::vector < MFItemBase*> test_items_;
//
//	json11::Json test_config_;
//	bool test_flag_;
//
//	HWND hwnd_for_test_;
//	UINT message_for_test_;
//
//};

class MFBase
{
public:
    // �⺻ ������
    MFBase();

    // �Ҹ���
    ~MFBase();

    // ���� ���� �Լ���, �ʱ�ȭ �۾��� �����ϴ� �޼���
    virtual int Init(void) = 0;

    // ���� ���� �Լ���, ��Ȱ��ȭ �۾��� �����ϴ� �޼���
    virtual int Deinit(void) = 0;

    // ���̺귯�� ID�� ��ȯ�ϴ� ���� ���� �Լ�
    virtual unsigned long GetLibId(void) = 0;

    // ���̺귯�� �̸��� ��ȯ�ϴ� ���� ���� �Լ�
    // �Ű�����: id - �̸��� ������ ����, len - ������ ����
    virtual int GetLibName(char* id, int len) = 0;

    // ���� ������ ��ȯ�ϴ� ���� ���� �Լ�
    virtual const std::string GetVersion(void) const = 0;

    // JSON ��ü�κ��� �������� �ε��ϴ� �Լ� (�⺻ ���� ����)
    // �Ű�����: config - JSON ���� ��ü
    virtual int Config(json11::Json& config) {
        return MFERR_NOERR; // ���� �� 0 ��ȯ
    }

    // �׽�Ʈ�� �����ϱ� �� �ʿ��� �۾��� �����ϴ� �Լ� (�⺻ ���� ����)
    virtual int PreTest(void) {
        return MFERR_NOERR; // ���� �� 0 ��ȯ
    }

    // �׽�Ʈ�� ���� �� ��ó���� �����ϴ� �Լ� (�⺻ ���� ����)
    virtual int PostTest(void) {
        return MFERR_NOERR; // ���� �� 0 ��ȯ
    }

    // �޽��� �ݹ� ó���� ���� �Լ� (�⺻ ���� ����)
    // �Ű�����: wp - WPARAM �޽���, lp - LPARAM �޽���
    virtual int MessageCallback(WPARAM wp, LPARAM lp) {
        return MFERR_NOERR; // ���� �� 0 ��ȯ
    }

    // �α� �޽����� ����ϴ� �Լ� ������
    void(*PrintLog)(const char* fmt, ...);

    // �׽�Ʈ �׸�(MFItemBase ��ü)�� ����� �����ϴ� ����
    std::vector < MFItemBase*> test_items_;

    // �׽�Ʈ ���� ������ �����ϴ� JSON ��ü
    json11::Json test_config_;

    // �׽�Ʈ ���¸� ��Ÿ���� �÷���
    bool test_flag_;

    // �׽�Ʈ�� ���� ���Ǵ� ������ �ڵ�
    HWND hwnd_for_test_;

    // �׽�Ʈ�� ���� ���Ǵ� �޽���
    UINT message_for_test_;
};
