This is self-learning project on c++ - game about the Last Mage and his attempt to destroy the Mage Slayers once and for all
It has gameplay core and UI separated, currently only console UI but plans include adding another UI on SFML
Game also has magic system with elements, status effects and element combination in powerful spells

### Classes UML
![Classes UML](Classes.png)

### Activities UML
![Activities UML](Activity.png)

### Core states UML

![Core states UML](CoreStates.png)

### Math models
AttackDamage = (damage + random(damageRand)) * (1 - frost)

- damage, damageRand - character parameters
- frost - element on enemy, more frost - lower damage

TakenDamage = AttackDamage * defence
- defence - character parameter
