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

// 외부에서 호출 가능한 DLL 함수 정의

// 라이브러리 초기화 함수
// - 로그 출력 함수 포인터(f)를 설정하고 라이브러리 정보(info)를 JSON 형식으로 반환
// - theApp 객체의 초기화 함수 호출
extern "C" __declspec(dllexport) int Init(void(*f)(const char* fmt, ...), char* info, int info_len) {
    // 로그 출력 함수 포인터 설정
    theApp.PrintLog = f;

    // 라이브러리 이름 가져오기
    char name[64];
    theApp.GetLibName(name, sizeof(name));

    // 라이브러리 정보 JSON 객체 생성
    json11::Json mflinfo = json11::Json(json11::Json::object{
        {"ID", (int)theApp.GetLibId()},          // 라이브러리 ID
        {"NAME", name},                          // 라이브러리 이름
        {"VERSION", theApp.GetVersion()},        // 라이브러리 버전
        {"ITEMS", json11::Json::array{}}         // 테스트 항목 리스트
        });

    // 테스트 항목 정보를 JSON에 추가
    int index = 0;
    for (auto& titem : theApp.test_items_) {
        titem->GetName(name, sizeof(name));
        mflinfo["ITEMS"].insert(index++, json11::Json::object{
            {"ID", (int)titem->id_},            // 항목 ID
            {"NAME", name}                      // 항목 이름
            });
    }

    // JSON 문자열로 변환하여 info에 복사
    int r = strcpy_s(info, info_len, mflinfo.dump(0).c_str());

    // 성공적으로 복사되었으면 라이브러리 초기화 호출
    if (r == 0) {
        r = theApp.Init();
    }
    return r;
}

// 라이브러리 종료 함수
// - theApp 객체의 종료 함수 호출
extern "C" __declspec(dllexport) int Deinit(void) {
    return theApp.Deinit();
}

// 테스트 사전 준비 함수
// - 테스트 메시지 핸들러 설정 및 테스트 구성 JSON 파싱
extern "C" __declspec(dllexport) int PreTest(HWND hwnd, UINT msg, const char* config) {
    std::string err, result;

    // 테스트 메시지 핸들러 설정
    theApp.hwnd_for_test_ = hwnd;
    theApp.message_for_test_ = msg;

    // 테스트 구성 JSON 파싱
    theApp.test_config_ = json11::Json::parse(config, err);

    // 테스트 플래그 활성화
    theApp.test_flag_ = true;

    // JSON 파싱 에러 체크
    if (err.empty() == false) {
        return MFERR_JSON_PARSING_ERR;
    }
    return theApp.PreTest();
}

// 특정 테스트 항목 실행 함수
// - 항목 ID로 테스트 항목을 식별하고 구성(config) 및 저장소(storage) 정보를 전달하여 테스트 수행
// - 결과(result)와 저장소를 업데이트
extern "C" __declspec(dllexport) int Test(int itemid, const char* config, char* storage_str, int storage_str_len, char* result_str, int result_str_len) {
    for (auto& titem : theApp.test_items_) {
        if (titem->id_ == itemid) {
            std::string err, result;

            // JSON 파싱 (테스트 구성)
            json11::Json cfg = json11::Json::parse(config, err);
            if (err.empty() == false) {
                return MFERR_JSON_PARSING_ERR;
            }

            // JSON 파싱 (저장소)
            json11::Json storage = json11::Json::parse(storage_str, err);
            if (err.empty() == false) {
                return MFERR_JSON_PARSING_ERR;
            }

            // 테스트 수행
            int r = titem->Test(cfg, storage, result);

            // 결과 문자열 복사
            int r2 = strcpy_s(result_str, result_str_len, result.c_str());
            if (r2 != 0) {
                return r2;
            }

            // 저장소 업데이트
            r2 = strcpy_s(storage_str, storage_str_len, storage.dump(0).c_str());
            if (r2 != 0) {
                return r2;
            }
            return r;
        }
    }
    return MFERR_INVALID_ID;
}

// 테스트 완료 처리 함수
// - PostTest() 호출로 테스트 후 처리
extern "C" __declspec(dllexport) int PostTest(void) {
    return theApp.PostTest();
}

// 설정 데이터 처리 함수
// - 설정 데이터를 JSON 형식으로 파싱, 업데이트, 반환
extern "C" __declspec(dllexport) int Config(char* config, int config_len) {
    std::string err, result;

    // JSON 파싱
    json11::Json cfg = json11::Json::parse(config, err);
    if (err.empty() == false) {
        return MFERR_JSON_PARSING_ERR;
    }

    // 설정 적용
    int r = theApp.Config(cfg);
    if (r == MFERR_NOERR) {
        // 설정 데이터 업데이트
        r = strcpy_s(config, config_len, cfg.dump(0).c_str());
    }
    return MFERR_NOERR;
}

// 특정 테스트 항목 설정 처리 함수
// - 항목 ID를 통해 테스트 항목 설정을 업데이트
extern "C" __declspec(dllexport) int TestItemConfig(int itemid, char* config, int config_len) {
    for (auto& titem : theApp.test_items_) {
        if (titem->id_ == itemid) {
            std::string err, result;

            // JSON 파싱
            json11::Json cfg = json11::Json::parse(config, err);
            if (err.empty() == false) {
                return MFERR_JSON_PARSING_ERR;
            }

            // 테스트 항목 설정 적용
            int r = titem->Config(cfg);
            if (r == MFERR_NOERR) {
                // 설정 데이터 업데이트
                r = strcpy_s(config, config_len, cfg.dump(0).c_str());
            }
            return MFERR_NOERR;
        }
    }
    return MFERR_INVALID_ID;
}

// 메시지 콜백 처리 함수
// - 워드파라미터(wp)와 롱파라미터(lp)를 theApp으로 전달
extern "C" __declspec(dllexport) int MessageCallback(WPARAM wp, LPARAM lp) {
    return theApp.MessageCallback(wp, lp);
}

// 테스트 중지 함수
// - 테스트 플래그를 비활성화하여 테스트 중단
extern "C" __declspec(dllexport) void StopTest(void) {
    theApp.test_flag_ = false;
}
