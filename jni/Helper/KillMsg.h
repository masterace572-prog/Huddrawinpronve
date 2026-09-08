
int (*orig_kill_message)(ASTExtraPlayerController* OwnerController, struct FFatalDamageParameter* FatalDamageParameter);
int hook__kill_message(ASTExtraPlayerController* OwnerController, struct FFatalDamageParameter* FatalDamageParameter)
{
    auto CurrentWeaponReplicated = Cheat::localPlayer->WeaponManagerComponent->CurrentWeaponReplicated;
    if (CurrentWeaponReplicated)
    {
        auto Weaponid = Cheat::localPlayer->WeaponManagerComponent->CurrentWeaponReplicated->GetWeaponID();
  
        if (FatalDamageParameter->CauserKey == Cheat::localController->PlayerKey)
        {
            if (Weaponid == 101004) 
            {//m4
                FatalDamageParameter->CauserWeaponAvatarID = 1101004046; // Set to the desired weapon ID
            }
		    if (Weaponid == 103002)
		    {//m24
                FatalDamageParameter->CauserWeaponAvatarID = 1103002087; // Set to the desired weapon ID
            }
		    if (Weaponid == 103007) 
		    {//mk14
                FatalDamageParameter->CauserWeaponAvatarID = 1103007028; // Set to the desired weapon ID
            }
		    if (Weaponid == 101007)
		    {//qbz
                FatalDamageParameter->CauserWeaponAvatarID = 1101007071; // Set to the desired weapon ID
            }
		    if (Weaponid == 101102) 
		    {//ace32
                FatalDamageParameter->CauserWeaponAvatarID = 1101102025; // Set to the desired weapon ID
            }
		    if (Weaponid == 102003) 
		    {//vec
                FatalDamageParameter->CauserWeaponAvatarID = 1102003080; // Set to the desired weapon ID
            }
            if (Weaponid == 101008) 
            { //m7
                FatalDamageParameter->CauserWeaponAvatarID = 1101008104; // Set to the desired weapon ID
            }
		    if (Weaponid == 102004) 
		    { //tom
                FatalDamageParameter->CauserWeaponAvatarID = 1102004034; // Set to the desired weapon ID
            }
            if (Weaponid == 102002) 
            {//ump
                FatalDamageParameter->CauserWeaponAvatarID = 1102002136; // Set to the desired weapon ID
            }
		    if (Weaponid == 102001) 
		    {//uzi
                FatalDamageParameter->CauserWeaponAvatarID = 1102001120; // Set to the desired weapon ID
            }
            if (Weaponid == 101001) 
            {//akm
                FatalDamageParameter->CauserWeaponAvatarID = 1101001265; // Set to the desired weapon ID
            }
            if (Weaponid == 101003) 
            {//scar
                FatalDamageParameter->CauserWeaponAvatarID = 1101003195; // Set to the desired weapon ID
            }
            if (Weaponid == 101006) 
            {//aug
                FatalDamageParameter->CauserWeaponAvatarID = 1101006075; // Set to the desired weapon ID
            }
		    if (Weaponid == 103003) 
		    {//awm
                FatalDamageParameter->CauserWeaponAvatarID = 1103003042; // Set to the desired weapon ID
            }
		    if (Weaponid == 105001)
		    {//m249
                FatalDamageParameter->CauserWeaponAvatarID = 1105001048; // Set to the desired weapon ID
            }
		    if (Weaponid == 105002) 
		    {//dp28
                FatalDamageParameter->CauserWeaponAvatarID = 1105002091; // Set to the desired weapon ID
            }
		    if (Weaponid == 103005) 
		    {//vss
                FatalDamageParameter->CauserWeaponAvatarID = 1103005024; // Set to the desired weapon ID
            }
		    if (Weaponid == 103001) 
		    {//k98
                FatalDamageParameter->CauserWeaponAvatarID = 1103001191; // Set to the desired weapon ID
            }
        }
    }
    return orig_kill_message(OwnerController, FatalDamageParameter);
}
/*
void (*orig_Broadcast)(ASTExtraPlayerController* thiz, struct FFatalDamageParameter* FatalDamageParameter);
void hk_Broadcast(ASTExtraPlayerController* thiz, struct FFatalDamageParameter* FatalDamageParameter)
{
    if (KillMessage) {
        if (Cheat::localController->PlayerKey == FatalDamageParameter->CauserKey)
        {
        int g_WeaponID = Cheat::localPlayer -> WeaponManagerComponent -> CurrentWeaponReplicated -> GetWeaponID();
            if (g_WeaponID == 101001) {
       if (preferences.AKM >= 1)
          FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.AKM;
       } else if (g_WeaponID == 101004) {
          if (preferences.M416 >= 1)
             FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.M416_1;
            }
            else if (g_WeaponID == 101003) {
                      if (preferences.SCARL >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.Scar;
        }
        else if (g_WeaponID == 103001) {
                  if (preferences.KAR98 >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = 1103001179;
        }
        else if (g_WeaponID == 103002) {
                          if (preferences.M24 >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.M24;
        }
        else if (g_WeaponID == 103003) {
        if (preferences.AWM >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.AWM;
        }
        else if (g_WeaponID == 101005) {
                if (preferences.GROZA >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.Groza;
        }
        else if (g_WeaponID == 101008) {
                        if (preferences.M762 >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.M762;
        }
        else if (g_WeaponID == 105001) {
                        if (preferences.M249 >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.M249;
        }
        else if (g_WeaponID == 105002) {
                  if (preferences.DP28 >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.DP28;
        }
        else if (g_WeaponID == 102001) {
                  if (preferences.UZI >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.UZI;
        }
        else if (g_WeaponID == 102002) {
                  if (preferences.UMP >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.UMP;
        }
        else if (g_WeaponID == 102003) {
                  if (preferences.VECTOR >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.Vector;
        }
        else if (g_WeaponID == 102004) {
                  if (preferences.TOMMY >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = 1102004034;
        }
        else if (g_WeaponID == 102005) {
                  if (preferences.BIZON >= 1)
            FatalDamageParameter -> CauserWeaponAvatarID = new_Skin.Bizon;
        }
            
            //add your shit here
            FatalDamageParameter->CauserClothAvatarID = new_Skin.XSuits;
        }
    }
    return orig_Broadcast(thiz, FatalDamageParameter);
}

if (KillMessage) {
                            int pController = 987;
                            auto VTable = (void **) Cheat::localController->VTable;
                            auto f_mprotect = [](uintptr_t addr, size_t len,
                            int32_t prot) -> int32_t {
                                static_assert(PAGE_SIZE == 4096);
                                constexpr
                                size_t page_size = static_cast<size_t>(PAGE_SIZE);
                                void *start = reinterpret_cast<void *>(addr & -page_size);
                                uintptr_t end = (addr + len + page_size - 20) & -page_size;
                                return mprotect(start, end -
                                                reinterpret_cast<uintptr_t>(start),
                                                prot);
                            };
                            if (VTable && (VTable[pController] != hk_Broadcast)) {
                                orig_Broadcast = decltype(orig_Broadcast)(
                                                     VTable[pController]);

                                f_mprotect((uintptr_t)(&VTable[pController]),
                                           sizeof(uintptr_t), PROT_READ | PROT_WRITE);
                                VTable[pController] = (void *) hk_Broadcast;
                            }
                        }*/
