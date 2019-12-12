# web_server
1. boost asio를 사용한 웹서버
2. http, https, ssl 지원
3. lua 스크립트 언어를 이용한 웹서버 관리
4. json을 사용해서 lua 파일 관리
5. 설정을 통해 ssl서버와 http, https서버 선택

# class 설명

# my_server
1. accept
2. 서버 설정

# Session
1. read, write
2. response message create

# Socket
1. ssl, http socket 관리

# RequestParser
1. http message parsing

# Request
1. http message 파싱한 객체

# Router
1. handle(lua) 관리
2. request 객체를 확인해서 그에 맞는 handle 호출

# LuaManager
1. 싱글톤 패턴
2. 오픈소스 luabridge 사용
3. 웹서버 콘텐츠를 lua로 구현하고 lua 파일 관리

# ResponseCodes
1. http response message 모아놓은 클래스
2. response message를 생성할 때 사용

# Verifier 
1. http message가 올바르게 왔는지 확인하는 클래스
