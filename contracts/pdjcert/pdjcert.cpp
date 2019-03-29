/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include "pdjcert.hpp"

namespace eosio {


//p
void pdjcert::mkcertname( name staff, string school, string memo )
{    
    require_auth(staff);
    //require_auth(worker);
    uint8_t status;
    
    if(staff.length()){
        eosio_assert(is_account(staff),"没有这个账户");
    	status = 1;
    }
    else{
    	status = 0;
    }
  
    certnames tk( _code, _code.value );

    for(auto obj = tk.begin() ; obj != tk.end() ; obj ++) {
        if (obj->certRemark == memo) {
            print("the cert's name is alreay exists!");
            return;
        }
    }

    tk.emplace( staff, [&](auto &t){
        t.staff  = staff;
        t.certnameID  = tk.available_primary_key();
        t.school   = school;
        t.status  = 0;
        t.certRemark  = memo;

    });
}

void pdjcert::disablecert( uint64_t certnameID, name staff)
{
	certnames tk( _code, _code.value );
	require_auth(staff);
    auto obj =  tk.find(certnameID);
    eosio_assert(obj != tk.end(), "failed to get certnameid");

    tk.modify(obj, staff, [&](auto &t){
        t.status = 1;
    });
	

}

void pdjcert::issuecert( uint64_t certnameID, name issuer, string userID, string memo )
{
    certnames tk( _code, _code.value );
	require_auth(issuer);
    auto obj =  tk.find(certnameID);
    eosio_assert(obj != tk.end(), "failed to get certnameid");

    certs tk1( _code, _code.value );
    for(auto obj = tk1.begin(); obj != tk1.end() ; obj ++ ) {
        eosio_assert(obj->UserID  != userID, "user's cert already exists!");
    }
    tk1.emplace(issuer,[&](auto &t){
        t.certID = tk.available_primary_key();
        t.certnameID = certnameID;
        t.issuer = issuer;
        t.issuetime = now();
        t.memo = memo;
        t.UserID = userID;
    });

}

void pdjcert::query( uint64_t certnameID, uint64_t certID, string userID )
{
    certs tk( _code, _code.value );
    auto obj = tk.find(certID);
    eosio_assert(obj != tk.end(),"failed to get cert info");
    print("The cert is ok!");
}

} /// namespace eosio

EOSIO_DISPATCH( eosio::pdjcert, (mkcertname)(disablecert)(issuecert)(query) )
//EOSIO_DISPATCH( eosio::token, (create)(issue)(transfer))
