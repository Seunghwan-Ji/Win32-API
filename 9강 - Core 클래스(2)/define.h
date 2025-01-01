#pragma once

// �̱��� ��ũ�� �Լ�
// #define SINGLE(type) public: static type* GetInst() {static type mgr; return &mgr;}
// mgr: manager ����

// \ �� ����ϸ� ���� �ٵ� ��ó���� ġȯ ������ ���ԵǾ� ��ũ�� ���Ǹ� �̾ �� �ִ�.
#define SINGLE(type) public:\
						 static type* GetInst()\
						 {\
							 static type mgr;\
							 \
							 return &mgr;\
						 }
