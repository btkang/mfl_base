#include "stdafx.h"
#include "mf_base.h"
#include "mfl_user.h"


MFBase::MFBase()
{
	test_flag_ = false;
}


MFBase::~MFBase()
{
	for (auto &titem : test_items_) {
		delete titem;
	}
}
//
//extern "C" __declspec(dllexport) int Init(void(*f)(const char *fmt, ...), char* info, int info_len) {
//	theApp.PrintLog = f;
//	char name[64];
//	theApp.GetLibName(name, sizeof(name));
//	json11::Json mflinfo = json11::Json(json11::Json::object{
//		{"ID", (int)theApp.GetLibId()},
//		{"NAME", name},
//		{"VERSION", theApp.GetVersion()},
//		{"ITEMS", json11::Json::array{}}
//		});
//	int index = 0;
//	for (auto &titem : theApp.test_items_) {
//		titem->GetName(name, sizeof(name));
//		mflinfo["ITEMS"].insert(index++, json11::Json::object{
//			{"ID", (int)titem->id_},
//			{"NAME", name} });
//	}
//	int r = strcpy_s(info, info_len, mflinfo.dump(0).c_str());
//	
//	if (r == 0) {
//		r = theApp.Init();
//	}
//	return r;
//}
//
//extern "C" __declspec(dllexport) int Deinit(void) {
//	return theApp.Deinit();
//}
//
//
//extern "C" __declspec(dllexport) int PreTest(HWND hwnd, UINT msg, const char* config) {
//	std::string err, result;
//	theApp.hwnd_for_test_ = hwnd;
//	theApp.message_for_test_ = msg;
//	theApp.test_config_ = json11::Json::parse(config, err);
//	theApp.test_flag_ = true;
//	if (err.empty() == false) {
//		return MFERR_JSON_PARSING_ERR;
//	}
//	return theApp.PreTest();
//}
//
//extern "C" __declspec(dllexport) int Test(int itemid, const char* config, char* storage_str, int storage_str_len, char* result_str, int result_str_len) {
//	for (auto &titem : theApp.test_items_) {
//		if (titem->id_ == itemid) {
//			std::string err, result;
//			json11::Json cfg = json11::Json::parse(config, err);
//			if (err.empty() == false) {
//				return MFERR_JSON_PARSING_ERR;
//			}
//			json11::Json storage = json11::Json::parse(storage_str, err);
//			if (err.empty() == false) {
//				return MFERR_JSON_PARSING_ERR;
//			}
//			int r = titem->Test(cfg, storage, result);
//			int r2 = strcpy_s(result_str, result_str_len, result.c_str());
//			if (r2 != 0) {
//				return r2;
//			}
//			r2 = strcpy_s(storage_str, storage_str_len, storage.dump(0).c_str());
//			if (r2 != 0) {
//				return r2;
//			}
//			return r;
//		}
//	}
//	return MFERR_INVALID_ID;
//}
//
//extern "C" __declspec(dllexport) int PostTest(void) {
//	int r;
//	r = theApp.PostTest();	
//	return r;
//}
//
//extern "C" __declspec(dllexport) int Config(char* config, int config_len) {
//	std::string err, result;
//	json11::Json cfg = json11::Json::parse(config, err);
//	if (err.empty() == false) {
//		return MFERR_JSON_PARSING_ERR;
//	}
//	int r;
//	r = theApp.Config(cfg);
//	if (r == MFERR_NOERR) {
//		r = strcpy_s(config, config_len, cfg.dump(0).c_str());
//	}
//	return MFERR_NOERR;
//}
//
//extern "C" __declspec(dllexport) int TestItemConfig(int itemid, char* config, int config_len) {
//	for (auto &titem : theApp.test_items_) {
//		if (titem->id_ == itemid) {
//			std::string err, result;
//			json11::Json cfg = json11::Json::parse(config, err);
//			if (err.empty() == false) {
//				return MFERR_JSON_PARSING_ERR;
//			}
//			int r = titem->Config(cfg);
//			if (r == MFERR_NOERR) {
//				r = strcpy_s(config, config_len, cfg.dump(0).c_str());
//			}
//			return MFERR_NOERR;
//		}
//	}
//	return MFERR_INVALID_ID;
//}
//
//extern "C" __declspec(dllexport) int MessageCallback(WPARAM wp, LPARAM lp) {
//	return theApp.MessageCallback(wp, lp);
//}
//
//extern "C" __declspec(dllexport) void StopTest(void) {
//	theApp.test_flag_ = false;
//}
//

// �ܺο��� ȣ�� ������ DLL �Լ� ����

// ���̺귯�� �ʱ�ȭ �Լ�
// - �α� ��� �Լ� ������(f)�� �����ϰ� ���̺귯�� ����(info)�� JSON �������� ��ȯ
// - theApp ��ü�� �ʱ�ȭ �Լ� ȣ��
extern "C" __declspec(dllexport) int Init(void(*f)(const char* fmt, ...), char* info, int info_len) {
    // �α� ��� �Լ� ������ ����
    theApp.PrintLog = f;

    // ���̺귯�� �̸� ��������
    char name[64];
    theApp.GetLibName(name, sizeof(name));

    // ���̺귯�� ���� JSON ��ü ����
    json11::Json mflinfo = json11::Json(json11::Json::object{
        {"ID", (int)theApp.GetLibId()},          // ���̺귯�� ID
        {"NAME", name},                          // ���̺귯�� �̸�
        {"VERSION", theApp.GetVersion()},        // ���̺귯�� ����
        {"ITEMS", json11::Json::array{}}         // �׽�Ʈ �׸� ����Ʈ
        });

    // �׽�Ʈ �׸� ������ JSON�� �߰�
    int index = 0;
    for (auto& titem : theApp.test_items_) {
        titem->GetName(name, sizeof(name));
        mflinfo["ITEMS"].insert(index++, json11::Json::object{
            {"ID", (int)titem->id_},            // �׸� ID
            {"NAME", name}                      // �׸� �̸�
            });
    }

    // JSON ���ڿ��� ��ȯ�Ͽ� info�� ����
    int r = strcpy_s(info, info_len, mflinfo.dump(0).c_str());

    // ���������� ����Ǿ����� ���̺귯�� �ʱ�ȭ ȣ��
    if (r == 0) {
        r = theApp.Init();
    }
    return r;
}

// ���̺귯�� ���� �Լ�
// - theApp ��ü�� ���� �Լ� ȣ��
extern "C" __declspec(dllexport) int Deinit(void) {
    return theApp.Deinit();
}

// �׽�Ʈ ���� �غ� �Լ�
// - �׽�Ʈ �޽��� �ڵ鷯 ���� �� �׽�Ʈ ���� JSON �Ľ�
extern "C" __declspec(dllexport) int PreTest(HWND hwnd, UINT msg, const char* config) {
    std::string err, result;

    // �׽�Ʈ �޽��� �ڵ鷯 ����
    theApp.hwnd_for_test_ = hwnd;
    theApp.message_for_test_ = msg;

    // �׽�Ʈ ���� JSON �Ľ�
    theApp.test_config_ = json11::Json::parse(config, err);

    // �׽�Ʈ �÷��� Ȱ��ȭ
    theApp.test_flag_ = true;

    // JSON �Ľ� ���� üũ
    if (err.empty() == false) {
        return MFERR_JSON_PARSING_ERR;
    }
    return theApp.PreTest();
}

// Ư�� �׽�Ʈ �׸� ���� �Լ�
// - �׸� ID�� �׽�Ʈ �׸��� �ĺ��ϰ� ����(config) �� �����(storage) ������ �����Ͽ� �׽�Ʈ ����
// - ���(result)�� ����Ҹ� ������Ʈ
extern "C" __declspec(dllexport) int Test(int itemid, const char* config, char* storage_str, int storage_str_len, char* result_str, int result_str_len) {
    for (auto& titem : theApp.test_items_) {
        if (titem->id_ == itemid) {
            std::string err, result;

            // JSON �Ľ� (�׽�Ʈ ����)
            json11::Json cfg = json11::Json::parse(config, err);
            if (err.empty() == false) {
                return MFERR_JSON_PARSING_ERR;
            }

            // JSON �Ľ� (�����)
            json11::Json storage = json11::Json::parse(storage_str, err);
            if (err.empty() == false) {
                return MFERR_JSON_PARSING_ERR;
            }

            // �׽�Ʈ ����
            int r = titem->Test(cfg, storage, result);

            // ��� ���ڿ� ����
            int r2 = strcpy_s(result_str, result_str_len, result.c_str());
            if (r2 != 0) {
                return r2;
            }

            // ����� ������Ʈ
            r2 = strcpy_s(storage_str, storage_str_len, storage.dump(0).c_str());
            if (r2 != 0) {
                return r2;
            }
            return r;
        }
    }
    return MFERR_INVALID_ID;
}

// �׽�Ʈ �Ϸ� ó�� �Լ�
// - PostTest() ȣ��� �׽�Ʈ �� ó��
extern "C" __declspec(dllexport) int PostTest(void) {
    return theApp.PostTest();
}

// ���� ������ ó�� �Լ�
// - ���� �����͸� JSON �������� �Ľ�, ������Ʈ, ��ȯ
extern "C" __declspec(dllexport) int Config(char* config, int config_len) {
    std::string err, result;

    // JSON �Ľ�
    json11::Json cfg = json11::Json::parse(config, err);
    if (err.empty() == false) {
        return MFERR_JSON_PARSING_ERR;
    }

    // ���� ����
    int r = theApp.Config(cfg);
    if (r == MFERR_NOERR) {
        // ���� ������ ������Ʈ
        r = strcpy_s(config, config_len, cfg.dump(0).c_str());
    }
    return MFERR_NOERR;
}

// Ư�� �׽�Ʈ �׸� ���� ó�� �Լ�
// - �׸� ID�� ���� �׽�Ʈ �׸� ������ ������Ʈ
extern "C" __declspec(dllexport) int TestItemConfig(int itemid, char* config, int config_len) {
    for (auto& titem : theApp.test_items_) {
        if (titem->id_ == itemid) {
            std::string err, result;

            // JSON �Ľ�
            json11::Json cfg = json11::Json::parse(config, err);
            if (err.empty() == false) {
                return MFERR_JSON_PARSING_ERR;
            }

            // �׽�Ʈ �׸� ���� ����
            int r = titem->Config(cfg);
            if (r == MFERR_NOERR) {
                // ���� ������ ������Ʈ
                r = strcpy_s(config, config_len, cfg.dump(0).c_str());
            }
            return MFERR_NOERR;
        }
    }
    return MFERR_INVALID_ID;
}

// �޽��� �ݹ� ó�� �Լ�
// - �����Ķ����(wp)�� ���Ķ����(lp)�� theApp���� ����
extern "C" __declspec(dllexport) int MessageCallback(WPARAM wp, LPARAM lp) {
    return theApp.MessageCallback(wp, lp);
}

// �׽�Ʈ ���� �Լ�
// - �׽�Ʈ �÷��׸� ��Ȱ��ȭ�Ͽ� �׽�Ʈ �ߴ�
extern "C" __declspec(dllexport) void StopTest(void) {
    theApp.test_flag_ = false;
}
