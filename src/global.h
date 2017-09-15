#ifndef GLOBAL_H
#define GLOBAL_H

namespace Constants {
namespace Property {
extern const char *Belligerent;
} // Constants::Properties
namespace Belligerent {
extern const char *Enemy;
extern const char *Player;
} // Constants::Belligerent

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
} // Constants::EnemyTank::Properties
namespace Type {
extern const char *Usual;
extern const char *TroopCarrier;
extern const char *Bursting;
extern const char *Armored;
} // Constants::EnemyTank::Type
} // Constants::EnemyTank
} // Constants

int randomNumber(int min, int max);

#endif // GLOBAL_H
