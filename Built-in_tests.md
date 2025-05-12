# BUILT-IN TESTS

*bash 쉘과 동작 비교하며 구현하기, 한 명령어 실행 후 echo $? 하여 return 값 확인하며 구현하기*

### 1. echo

* [X] echo
* [X] echo aaa
* [X] echo bbb
* [X] echo a b c d e
* [X] echo $
* [X] echo -n
* [X] echo -nnnnnn -nnnnnn
* [X] echo -nnn -nn -na abc
* [X] echo -n aaa
* [X] echo -nnnnnn -nn b
* [X] echo $?

  *(히어독 사용 시)5. echo -n 123 >> a (printf() 사용시 화면에 출력되고, 파일에 안들어감. write() 사용시 정상 작동)*

### 2. exit

1. long long 범위 내의 숫자값이 입력되면 ~~(unsigned int)ft_atoi(cmd->argv[1]) % 256 값이 들어감~~ 마지막 byte 값만 가져옴(exit 이 알아서 함!)
   * [X] ./minishell -> exit(마지막 명령 성공/실패 경우 이후 각각 테스트)
   * [X] exit -1 (return: 255)
   * [X] exit -2 (return: 254)
   * [X] exit 0  (return: 0)
   * [X] exit 1  (return: 1)
2. 숫자가 아니거나 long long 범위 넘어가면 에러 메시지 발생(numeric argument required), 리턴 값은 2
   * [X] ./minishell -> exit 9223372036854775807(LLMAX) (return: 255)
   * [X] -> exit 9223372036854775808     (numeric error, return: 2)
   * [X] -> exit -9223372036854775808    (return: 0)
   * [X] -> exit -9223372036854775809    (numeric error, return: 2)
   * [X] ./minishell -> exit a (numeric error, return: 2)
3. 여러 개의 인자가 있을 때: 첫 번째 인자부터 검사 시작. 첫 번째 인자가 오류가 아니면 다음 인자가 있는지 보고, 다음 인자 있으면 에러 메시지 발생(too many arguments), 리턴 값은 1
   * [X] ./minishell -> exit 2 b c
   * [X] -> exit 1 a
   * [X] -> exit 9223372036854775808 2 3

### 3. env

* [X] env

* 출력 결과가 어떤 순서로 출력되는지는 정해진 표준이 없음을 설명
* env는 value가 NULL인 환경변수는 출력하지 않음
* 항상 _ 환경변수가 마지막에 출력
* 환경변수 의미 및 역할

### 4. export

  환경변수 이름은 숫자로 시작할 수 없음. _ 외의 특수문자는 사용할 수 없음

* [X] export (declare -x 어쩌고 출력됨)
  export 출력은 env와 달리 각 줄마다 declare -x가 붙고, value가 큰따옴표로 감싸짐
  _ 환경변수는 출력 X
  declare -x 의미?
* [X] export 1=a (bash: export: `1=a': not a valid identifier, return: 1)

  * [X] return 값 설정이 되어있지 않음!
* [X] export _a=a (환경변수 목록에 _a가 추가되며, 그 값은 a임)
* [X] export a (value가 NULL) : 에러 메시지가 출력되지는 않으나(return: 0) 환경변수에 추가되지도 않음
* [X] export a=b (환경변수 목록에 a가 추가되며, 그 값은 b임)
* [X] export a (이미 value가 존재하는 환경변수라면, = 없이 export 했을 때 값이 변하지 않음)
* [X] export = (bash: export: `=': not a valid identifier, return: 1)

  * [X] return 값 설정이 되어있지 않음!
* [X] export $=a (bash: export: $1=a': not a valid identifier, return: 1)

  * [X] return 값 설정이 되어있지 않음!
* [ ] ~~export $LOGNAME=111 (에러 메시지를 출력하진 않으나, LOGNAME 환경변수 값이 변경되지도 않음)~~
  -> 이것도 mandatory 요구사항은 아닌 것 같습니다...
* [X] export b= (value가 빈문자열) (없던 환경변수라면 환경변수에 추가되며, 값이 없음. value가 존재하던 환경변수라면 그 값이 NULL로 대체됨)
* [X] export 1=a _a=a a=b b= = =111 c

  * [X] 정상적인 환경변수만 삽입하고
  * [X] 그 외에는 에러 메시지를 출력함
* [X] export e e (에러 메시지를 출력하진 않지만 아무 동작도 하지 않음)
* [X] export f 후 export f
* [ ] ~~export z=a 후 export z+=b (z의 값이 ab가 됨)~~
  -> mandatory 구현사항 아닌 듯 합니다...
* [ ] unset z 후 export z+=a 후 export z+=b

  * [X] unset z 후 export z=a 후 export z=b

---

끄아아아아아아앙ㄱ

* [ ] export Z
  -> env에 출력 X | export `declare -x Z` 출력됨
* [ ] export Z=
  -> env에 `Z=` 출력됨 | export `declare -x Z=""` 출력됨
* [ ] export Z=z
  -> env에 `Z=z` 출력됨 | export `declare -x Z="z"` 출력됨
* [ ] export Z	**->**	export Z=
  -> env에 `Z=` 출력됨 | export `declare -x Z=""` 출력됨
* [ ] export Z	**->**	export Z=z
  -> env에 `Z=z` 출력됨 | export `declare -x Z="z"` 출력됨
* [ ] export Z=	**->**	export Z=z
  -> env에 `Z=z` 출력됨 | export `declare -x Z="z"` 출력됨
* [ ] export Z=	**->**	export Z
  -> env에 `Z=` 출력됨 | export `declare -x Z=""` 출력됨
* [ ] export Z=z	**->**	export Z
  -> env에 `Z=z` 출력됨 | export `declare -x Z="z"` 출력됨
* [ ] export Z=z	**->**	export Z=
  -> env에 `Z=` 출력됨 | export `declare -x Z=""` 출력됨
  ***즉, 처음 입력할 땐 다르지만 key가 입력되고 난 뒤에는 어떻게든 export에 출력되는 형식으로 바뀜***

### 5. unset

* [X] unset -> 아무 동작 하지 않음

  ~~-> 현재 `unset: not enough arguments` error message 뜨는 중.~~
* [X] unset NOTEXIST (없는 환경변수를 unset하려 할 때) -> 아무 동작 하지 않음
* [ ] unset PATH(external 명령어는 실행 안되고, 빌트인은 실행 됨)

  * 빌트인 실행됨
* [ ] unset _ 이후

  1) env 해도 env 출력은 변경 X
     * **현재 _ 없어짐.**
  2) unset _ 해도 명령어 실행과 동시에 _가 다시 설정되어 무의미
* [ ] export a b c 이후 unset a _ c d e

  **-> 현재 _ 함께 없어짐, 이외 문제 없음!**
* [X] export a -> unset a -> export a -> export a
* [X] 일반적인 No such file or directory 는 echo \$?가 127 but cd에서의 No such file or directory은 echo $?가 1

### 6. cd

* [ ] cd 사용하면서 프롬프트에 표시된 현재 디렉토리 항목이 변경됨을 보임
* [X] echo \~~$~~~~OLDPWD~~ \$PWD 로 환경변수 값 변경 수시로 확인
  **-> $PWD 갱신 완료**
  ~~-> $OLDPWD 갱신 필요~~
* [X] cd a b (2개 이상의 인자가 주어질 때)
* [X] cd NOTEXIST (없는 디렉토리로 이동하려 할 때)

  ***(아래 사항들은 mandatory에서 요구하지 않은 사항이라 생각해서 따로 빼둡니다..)***
  ~~5. cd, cd -, cd ~ 설명
  6. HOME 값으로 이동하면 프롬프트 표시 경로가 ~로 바뀜
  7. HOME 경로에서 특정 디렉토리(mkdir a 후 cd a 등)로 이동했을 시, ~/a 등으로 표시됨을 보임
  8. HOME 값 바꾼 뒤 그 경로로 들어가서 그 경로에서 프롬프트 표시 경로가 ~로 뜨는 것을 보임
  9. cd '', cd "" --> 현재 경로로 이동
  10. cd, unset HOME 후 cd
  11. cd -, unset OLDPWD 후 cd -
  12. cd ~, unset HOME 후 cd ~ (cd와 cd ~의 차이점 설명)
  (cd ~ 은 HOME이 있으면 HOME으로 이동, 없으면 getent passwd uid에 있는 homedir로 이동)
  13. PWD 지우고 디렉토리 이동시 OLDPWD value가 NULL
  14. PWD, OLDPWD는 unset 하더라도, 그 바로 다음 디렉토리 이동시 환경변수가 아닌 일반 쉘 변수로 생성됨
  (그러나 쉘 변수 구현은 pdf 구현 사항이 아니므로 미구현)
  15. 파싱)
  ~는 따옴표로 둘러쌓이지 않았고 토큰 첫 글자가 ~이며, 바로 다음글자로 따옴표가 오지 않고, 다음 글자가 '/' 이거나 공백인 경우만 치환됨. (~~, '', '' 같은 경우는 치환 X)
  ~는 cd에서 치환되는것이 아니라 파싱 단계에서 치환됨
  HOME이 존재하고, value가 NULL이 아닐 경우에만 ~가 HOME 환경변수 값으로 치환되고,
  그 외에는 getent passwd uid에 있는 homedir로 이동
  단, heredoc(<<)의 limiter에 ~가 오는 경우는 치환 안됨
  16. 심볼릭 링크로 이동 후 cd ..~~

  1) ~~cd goinfree -> cd ..~~
  2) ~~/ 에서 cd bin (/usr/bin 심볼릭 링크) -> cd .. 했을 때, /usr로 이동하지 않고, /로 이동.
     PWD 값은 cd bin 이후에 /usr/bin이 아닌 /bin이 됨. cd .. 이후에는 /usr이 아닌 /가 됨.~~
  3) ~~정제되지 않은 디렉토리 문자열(////bin////../bin/usr 등)을 전달한 chdir() 실행 이후의 getcwd() 결과를       PWD에 넣는 것이 아니라, 디렉토리 문자열을 정제한 이후에 chdir()에 전달하고, chdir()이 성공하면 이 정제   된 디렉토리 문자열을 PWD에 넣는것이 이 때문. 또한 PWD에 저장함과 동시에 별도의 멤버 변수에도 따로     저장(pwd 명령어에 사용).~~

### 7. pwd

* [X] 심볼릭 링크로 이동 후 pwd -> cd .. 이후 pwd
* [X] PWD에 저장된 값을 출력하는 것이 아님
* [X] PWD와 무관함. 삭제해도 pwd로는 현재 경로가 정상 출력됨.
  -> cd 할 때, PWD외에도 별도의 멤버변수에도 경로를 저장한 이유. pwd에서는 이 멤버 변수 값을 출력.
