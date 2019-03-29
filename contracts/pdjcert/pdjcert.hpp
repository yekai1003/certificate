/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   
class [[eosio::contract]] pdjcert : public contract {
   public:
      pdjcert(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

      //创建证书类型
      [[eosio::action]]
      void mkcertname( name staff, string school, string memo );
      //使证书类型失效
      [[eosio::action]]
      void disablecert( uint64_t certnameID, name staff);
      //颁发证书
      [[eosio::action]]
      void issuecert( uint64_t certnameID, name issuer, string userID, string memo );
      //查询证书
      [[eosio::action]]
      void query( uint64_t certnameID, uint64_t certID, string userID );

   private:

      struct [[eosio::table]] certname {
         uint64_t    certnameID;
         name        staff; 
         string      school;
         string      certRemark;
         uint8_t     status;

         uint64_t primary_key()const { return certnameID; }
      };

      struct [[eosio::table]] cert {
         uint64_t    certID;
         uint64_t    certnameID;
         name        issuer; 
         uint64_t    issuetime;
         string      memo;
         string      UserID;

         uint64_t primary_key()const { return certID; }
      };

      typedef eosio::multi_index< "certs"_n, cert > certs;
      typedef eosio::multi_index< "certnames"_n, certname > certnames;
   private:
   
};

} /// namespace eosio
