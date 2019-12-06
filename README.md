# web_server
boost asio를 사용한 웹서버
http, https, ssl 지원
lua 스크립트 언어를 이용한 웹서버 관리
json을 사용해서 lua 파일 관리
설정을 통해 ssl서버와 http, https서버 선택

# class 설명

# my_server
accept
서버 설정

# Session
read, write
response message create

# Socket
ssl, http socket 관리

# RequestParser
http message parsing

# Request
http message 파싱한 객체

# Router
handle(lua) 관리
request 객체를 확인해서 그에 맞는 handle 호출

#LuaManager
싱글톤 패턴
오픈소스 luabridge 사용
웹서버 콘텐츠를 lua로 구현하고 lua 파일 관리

# ResponseCodes
http response message 모아놓은 클래스
response message를 생성할 때 사용

# Verifier 
http message가 올바르게 왔는지 확인하는 클래스
