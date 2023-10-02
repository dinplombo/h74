#ifndef VAULT_SECRETS_HPP
#define VAULT_SECRETS_HPP

#include <map>
#include <string>
#include <iostream>

#include "encoder.hpp"

using namespace AbsMessage;

namespace vault {

template<typename Secret>
class VaultSecrets {
public:
    static VaultSecrets& get_instance() noexcept; //keep the noexecpt?
    
public:
    ~VaultSecrets() noexcept = default;
    VaultSecrets(VaultSecrets const& a_other) = delete;
    VaultSecrets& operator=(VaultSecrets const& a_other) = delete;

    bool add(std::string const& a_key, Secret a_secret) noexcept; 
    bool get(std::string const& a_key, Secret& a_secret) const noexcept; 
    void save(std::ostream& a_destination, Encoder& a_encode) const; //encoder dont get const

private:
    VaultSecrets();

private:
    static VaultSecrets* s_instance;

private:
    std::map<std::string, Secret> m_secret_container;
    
};

template<typename Secret>
void load(VaultSecrets<Secret>& a_vault, std::istream& a_destination, Encoder& a_encode);

} //namespace vault

#include "inl/vault_secrets.hxx"

#endif // VAULT_SECRETS_HPP
