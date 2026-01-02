#include "pch.h"
#include "Character.h"
#include "AttackAction.h"
#include "Action.h"

//stats에 초기화 필요

Character::Character(string inName ) 
{
	//Player, Monster 생성자에 AddActions 추가 필요
	//AddActions(make_unique<Attack>());	// Player, Monster 둘 다 추가
	//AddActions(make_unique<UseItem>());
	// 
	// Player만 추가

	stats.name = inName;
}

void Character::AddActions(unique_ptr<Action> action)
{
	actions.push_back(move(action));
}

void Character::PlayAction(size_t index, ActionContext& context)
{
	//owner를 이 함수를 호출하는 객체로 설정
	context.owner = this;
 
	//actions vector의 index 번호의 action을 실행
	actions[index]->Play(context);
}

void Character::TakeDamage(int amount)
{
	stats.currentHealth = max(0, stats.currentHealth - amount);

	DeadEvent();
}

void Character::DeadEvent()
{
	if (stats.currentHealth <= 0)
		stats.bIsDead = true;
}

/*
void Character::printImage(int index)
{
    const std::vector<std::string> MonsterImages = {
        R"(
          .--------._
         (`--'       `-.
          `.______      `.
       ___________`__     \
    ,-'           `-.\     |
   //                \|    |\
  (`  .'~~~~~---\     \'   | |
   `-'           )     \   | |
      ,---------' - -.  `  . '
    ,'             `%`\`     |
   /                      \  |
  /     \-----.         \    `
 /|  ,_/ _..._'-._            |
(-'  / .' .-. '. /            `     
,`--< (  ( o )  )|        \     \
\ |  \ `._'-'_.'/%%             `\
 |/   \___```---'--`%        \     \
 |    '           `               \ \
 |                                   |
  `--.__                             |
        `---._______                 |
                    `.               |
                      \              |
        )",
        R"(
        =*===
       $$- - $$$
       $ <    D$$
       $ -   $$$
 ,     $$$$  |
///; ,---' _ |----.
 \ )(           /  )
 | \/ \.   '  _.|  \              $
 |  \ /(   /    /\_ \          $$$$$
  \ /  (       / /  )         $$$ $$$
       (  ,   /_/ ,`_,-----.,$$  $$$
       |   <----|  \---##     \   $$
       /         \\\           |    $
      '   '                    |
      |                 \      /
      /  \_|    /______,/     /
     /   / |   /    |   |    /
    (   /--|  /.     \  (\  (_
     `----,( ( _\     \ / / ,/
           | /        /,_/,/
          _|/        / / (
         / (        ^-/, |
        /, |          ^-    
        ^-
        )",
         R"(
         __.,,------.._
      ,'"   _      _   "`.
     /.__, ._  -=- _"`    Y
    (.____.-.`      ""`   j
     VvvvvvV`.Y,.    _.,-'       ,     ,     ,
        Y    ||,   '"\         ,/    ,/    ./
        |   ,'  ,     `-..,'_,'/___,'/   ,'/   ,
   ..  ,;,,',-'"\,'  ,  .     '     ' ""' '--,/    .. ..
 ,'. `.`---'     `, /  , Y -=-    ,'   ,   ,. .`-..||_|| ..
ff\\`. `._        /f ,'j j , ,' ,   , f ,  \=\ Y   || ||`||_..
l` \` `.`."`-..,-' j  /./ /, , / , / /l \   \=\l   || `' || ||...
 `  `   `-._ `-.,-/ ,' /`"/-/-/-/-"'''"`.`.  `'.\--`'--..`'_`' || ,
            "`-_,',  ,'  f    ,   /      `._    ``._     ,  `-.`'//         ,
          ,-"'' _.,-'    l_,-'_,,'          "`-._ . "`. /|     `.'\ ,       |
        ,',.,-'"          \=) ,`-.         ,    `-'._`.V |       \ // .. . /j
        |f\\               `._ )-."`.     /|         `.| |        `.`-||-\\/
        l` \`                 "`._   "`--' j          j' j          `-`---'
         `  `                     "`,-  ,'/       ,-'"  /
                                 ,'",__,-'       /,, ,-'
                                 Vvv'            VVv'
        )",
         R"(
         ,-.        ____
       ,-. /       ()__ \____
      /  //           _-()__ \-_
      \  ||  ,-.    _-     , /  -_
       \  \\/  |   _-      ./     -_
        \ ,-. /   /"\  /"\        _-
        ,-. //    \O/  \O/       _-
       /  // `.     ,-.         _-
       \  ||`.,-.   `._;       _-
        \  \\/  |`.   -_      _-
         \  /  /`. `. /////\\\\
          \   /   `. /  ,--,  /
           \  `.    |   `,  \ |
            `.  `.  /    :  / /       _-.
              `.  `.    ,` / |      _- . \
                `.  `.,`  /  /    _- .  \/
                  `.     |  |   _- .  \ /
                  | `.   /  / _- .  \  /
                 /    `._)  /-  . \   /
                |           `.   \  ,`
               /              \   ,`
               |                ,`
        )",
    };
    std::cout << MonsterImages[index] << std::endl;
}
  */
