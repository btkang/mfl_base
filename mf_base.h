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

// MFItemBase 클래스: 검사 항목의 기본 클래스를 정의합니다.
// 이 클래스는 다른 검사 항목 클래스들이 상속받아 구현할 인터페이스를 제공합니다.
class MFItemBase {
public:
    // 생성자: 객체를 생성할 때 검사 항목 ID를 초기화합니다.
    // id: 검사 항목을 식별하는 고유 ID.
    MFItemBase(unsigned long id) : id_(id) {}

    // 소멸자: 객체가 소멸될 때 호출됩니다.
    // 가상 소멸자를 사용하여 상속받은 클래스의 자원이 올바르게 해제되도록 보장합니다.
    virtual ~MFItemBase() {}

    // 검사 항목 ID를 저장하는 멤버 변수입니다.
    unsigned long id_;

    // GetName 함수: 검사 항목의 이름을 가져옵니다.
    // 이 함수는 순수 가상 함수로, 상속받은 클래스에서 반드시 구현해야 합니다.
    // name: 검사 항목의 이름을 저장할 버퍼.
    // size: 버퍼의 크기.
    // 반환값: 함수 호출 성공 여부를 나타내는 정수 값.
    virtual int GetName(char* name, int size) const = 0;

    // Test 함수: 주어진 설정(config)을 기반으로 검사 작업을 수행합니다.
    // config: 검사 설정을 포함하는 JSON 객체.
    // storage: 검사 결과 데이터를 저장할 JSON 객체.
    // result: 검사 결과를 문자열로 저장할 변수.
    // 반환값: 검사 결과 상태를 나타내는 정수 값.
    virtual int Test(const json11::Json& config, json11::Json& storage, std::string& result) const = 0;

    // Config 함수: 검사 항목의 설정(config)을 반환합니다.
    // 이 함수는 기본적으로 아무 작업도 하지 않으며 상속받은 클래스에서 필요에 따라 재정의할 수 있습니다.
    // config: 설정 데이터를 저장할 JSON 객체.
    // 반환값: 함수 호출 성공 여부를 나타내는 정수 값.
    virtual int Config(json11::Json& config) const {
        // 기본 반환값으로 오류가 없음을 나타냅니다.
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
    // 기본 생성자
    MFBase();

    // 소멸자
    ~MFBase();

    // 순수 가상 함수로, 초기화 작업을 정의하는 메서드
    virtual int Init(void) = 0;

    // 순수 가상 함수로, 비활성화 작업을 정의하는 메서드
    virtual int Deinit(void) = 0;

    // 라이브러리 ID를 반환하는 순수 가상 함수
    virtual unsigned long GetLibId(void) = 0;

    // 라이브러리 이름을 반환하는 순수 가상 함수
    // 매개변수: id - 이름을 저장할 버퍼, len - 버퍼의 길이
    virtual int GetLibName(char* id, int len) = 0;

    // 버전 정보를 반환하는 순수 가상 함수
    virtual const std::string GetVersion(void) const = 0;

    // JSON 객체로부터 설정값을 로드하는 함수 (기본 구현 제공)
    // 매개변수: config - JSON 설정 객체
    virtual int Config(json11::Json& config) {
        return MFERR_NOERR; // 성공 시 0 반환
    }

    // 테스트를 시작하기 전 필요한 작업을 수행하는 함수 (기본 구현 제공)
    virtual int PreTest(void) {
        return MFERR_NOERR; // 성공 시 0 반환
    }

    // 테스트가 끝난 후 후처리를 수행하는 함수 (기본 구현 제공)
    virtual int PostTest(void) {
        return MFERR_NOERR; // 성공 시 0 반환
    }

    // 메시지 콜백 처리를 위한 함수 (기본 구현 제공)
    // 매개변수: wp - WPARAM 메시지, lp - LPARAM 메시지
    virtual int MessageCallback(WPARAM wp, LPARAM lp) {
        return MFERR_NOERR; // 성공 시 0 반환
    }

    // 로그 메시지를 출력하는 함수 포인터
    void(*PrintLog)(const char* fmt, ...);

    // 테스트 항목(MFItemBase 객체)의 목록을 저장하는 벡터
    std::vector < MFItemBase*> test_items_;

    // 테스트 설정 정보를 저장하는 JSON 객체
    json11::Json test_config_;

    // 테스트 상태를 나타내는 플래그
    bool test_flag_;

    // 테스트를 위해 사용되는 윈도우 핸들
    HWND hwnd_for_test_;

    // 테스트를 위해 사용되는 메시지
    UINT message_for_test_;
};
