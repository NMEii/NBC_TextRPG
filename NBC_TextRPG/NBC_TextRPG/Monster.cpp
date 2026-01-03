#include"pch.h"
#include "Monster.h"
#include "AttackAction.h"
#include "Random.h"

Monster::Monster()
{
}

//입력 받을때
Monster::Monster(std::string name, int playerLevel, int _artIndex) :Character(name)
{
    artIndex = _artIndex;
	stats.currentHealth = playerLevel * Random::Choice(20, 30);
	stats.maxHealth = playerLevel * Random::Choice(20, 30);
	stats.attack = playerLevel * Random::Choice(5, 10);

	AddActions(std::make_unique<AttackAction>());
}

Monster::~Monster()
{
}

string Monster::GetMonsterName()
{
	return stats.name;
}

void Monster::AttackTarget(Character* target)
{
	ActionContext ctx;
	ctx.target = target;

	PlayAction(0, ctx);
}

string Monster::GetImageString() const
{
    return MonsterImages[artIndex];
}


const std::vector<std::string> Monster::MonsterImages = {
        R"(
        .--------._
       (`--'        ` -.
        `.______         `.
       ___________`__      \
    ,-'            `-.\     |
   //                \|     |\
  (`  .'~~~~~---\      \'   | |
   `-'           )      \   | |
      ,---------' - -.  `   . '
    ,'              `%`\`      |
   /                     \     |
  /      \-----.          \    `
 /|  ,_/ _..._'-._              |
(-'  / .' .-. '. /               `      
,`--< (  ( o )  )|         \      \
\ |  \ `._'-'_.'/%%               `\
 |/   \___```---'--`%         \     \
 |    '           `              \   \
 |                                   |
 `--.__                              |
       `---._______                  |
                   `.                |
                     \               |
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
   ..  ,;,,',-'"\,'  ,  .     '     ' ""' '--,/    ..
 ,'. `.`---'     `, /  , Y -=-    ,'   ,   ,. .`-..||
ff\\`. `._        /f ,'j j , ,' ,   , f ,  \=\ Y   ||
l` \` `.`."`-..,-' j  /./ /, , / , / /l \   \=\l   ||
 `  `   `-._ `-.,-/ ,' /`"/-/-/-/-"'''"`.`.  `'.\--`'
            "`-_,',  ,'  f    ,   /      `._    ``._ 
          ,-"'' _.,-'    l_,-'_,,'          "`-._ . "
        ,',.,-'"          \=) ,`-.         ,    `-'._
        |f\\               `._ )-."`.     /|         
        l` \`                 "`._   "`--' j         
         `  `                     "`,-  ,'/       ,-'
                                 ,'",__,-'       /,, 
                                 Vvv'            VVv'
        )",
};
