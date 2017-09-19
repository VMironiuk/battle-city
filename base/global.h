#ifndef GLOBAL_H
#define GLOBAL_H

namespace Base {

namespace Constants {
namespace Property {
extern const char *Belligerent;
} // Constants::Properties
namespace Belligerent {
extern const char *Enemy;
extern const char *Player;
} // Constants::Belligerent
namespace Bonus {
namespace Property {
extern const char *Type;
} // Constants::Bonus::Property
enum BonusType {
    Grenade,
    Helmet,
    Shovel,
    Star,
    Tank,
    Timer
};
} // Constants::Bonus

namespace Projectile {
namespace Property {
extern const char *Powerful;
} // Constants::Projectile::Properties
} // Constants::Projectile

namespace PlayerTank {
namespace Property {
extern const char *Improvement;
} // Constants::PlayerTank::Properties
namespace Improvement {
extern const char *NoStars;
extern const char *OneStar;
extern const char *TwoStars;
extern const char *ThreeStars;
} // Constants::PlayerTank::Improvement
} // Constants::PlayerTank

namespace EnemyTank {
namespace Property {
extern const char *Type;
extern const char *Strength;
extern const char *Value;
} // Constants::EnemyTank::Properties
namespace Type {
extern const char *Usual;
extern const char *TroopCarrier;
extern const char *Bursting;
extern const char *Armored;
} // Constants::EnemyTank::Type
enum Value {
    Usual = 100,
    TroopCarrier = 200,
    Bursting = 300,
    Armored = 400
};// Constants::EnemyTank::Value
} // Constants::EnemyTank
} // Constants

}  // namespace Base

#endif // GLOBAL_H
