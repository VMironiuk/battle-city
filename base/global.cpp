#include "global.h"

namespace Base {

namespace Constants {
namespace Property {
const char *Belligerent = "belligerent";
} // Constants::Properties
namespace Belligerent {
const char *Enemy = "enemy";
const char *Player = "player";
} // Constants::Belligerent
namespace Bonus {
namespace Property {
const char *Type = "type";
} // Constants::Bonus::Property
} // Constants::Bonus

namespace Projectile {
namespace Property {
const char *Powerful = "powerful";
} // Constants::Projectile::Properties
} // Constants::Projectile

namespace PlayerTank {
namespace Property {
const char *Improvement = "improvement";
} // Constants::PlayerTank::Properties
namespace Improvement {
const char *NoStars = "no_stars";
const char *OneStar = "one_star";
const char *TwoStars = "two_stars";
const char *ThreeStars = "three_sars";
} // Constants::PlayerTank::Improvement
} // Constants::PlayerTank

namespace EnemyTank {
namespace Property {
const char *Type = "type";
const char *Strength = "strength";
const char *Value = "value";
} // Constants::EnemyTank::Properties
namespace Type {
const char *Usual = "usual";
const char *TroopCarrier = "armored_troop_carrier";
const char *Bursting = "bursting";
const char *Armored = "armored";
} // Constants::EnemyTank::Type
} // Constants::EnemyTank
} // Constants

}  // namespace Base
