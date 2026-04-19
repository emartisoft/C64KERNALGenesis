#pragma once
// license_check.h  --  PUBLIC header (static lib kullanıcısına görünür)
// rom_id ve iç mantık tamamen gizli — sadece 2 parametre yeterli.

/// module_dir  : "modules/" gibi arama dizini
/// module_name : modül adı ("patch_nes" gibi, .m64 uzantısı eklenir)
/// Dönüş       : lisans geçerliyse true
bool license_validate(const char* module_dir,
                      const char* module_name);
