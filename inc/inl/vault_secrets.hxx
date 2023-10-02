#ifndef VAULT_SECRETS_HXX
#define VAULT_SECRETS_HXX

#include "vault_secrets.hpp"
#include "text_message.hpp"



using namespace AbsMessage;

namespace vault {

template<typename Secret>
VaultSecrets<Secret>::VaultSecrets()
: m_secret_container{}
{
}

template<typename Secret>
VaultSecrets<Secret>& VaultSecrets<Secret>::get_instance() noexcept
{
    static VaultSecrets* ptr_vault = new VaultSecrets();
    return *ptr_vault;
}

template<typename Secret>
bool VaultSecrets<Secret>::add(std::string const& a_key, Secret a_secret) noexcept
{
    if (m_secret_container.count(a_key) > 0){
        return false;
    }
    m_secret_container[a_key] = a_secret;
    return true;
}

template<typename Secret>
bool VaultSecrets<Secret>::get(std::string const& a_key, Secret& a_secret) const noexcept
{
    auto it_secret  = m_secret_container.find(a_key);
    if (it_secret != m_secret_container.end()){
        a_secret = it_secret->second;
        return true;
    }
    return false;
}

namespace {

template<typename Secret>
std::string encoded_secrets(std::pair<std::string, Secret> a_key_and_secret, Encoder& a_encode)
{
    std::string line = a_key_and_secret.first + " " + a_key_and_secret.second;
    TextMessage str(line);
    TextMessage encoded;
    a_encode.encode(str, encoded);
    std::string result;

    for (auto char_str : encoded){
        result.push_back(char_str);
    }
    return result;
}

template<typename Secret>
Secret decode_secret(Secret& a_secret, Encoder& a_encode)
{
    TextMessage str(a_secret);
    TextMessage encoded;
    a_encode.encode(str, encoded);
    Secret result;

    for (auto char_str : encoded){
        result.push_back(char_str);
    }
    return result;
}
   
} //namespace

template<typename Secret>
void VaultSecrets<Secret>::save(std::ostream& a_destination, Encoder& a_encode) const
{
    for(std::pair<std::string, Secret> key_and_secret : m_secret_container){
        a_destination << encoded_secrets(key_and_secret, a_encode) << '\n';
    }
}

template<typename Secret>
void load(VaultSecrets<Secret>& a_vault, std::istream& a_source, Encoder& a_encode)
{
    std::string key;
    Secret secret;

    while (a_source >> key >> secret){
        a_vault.add(decode_secret<std::string>(key, a_encode), decode_secret<Secret>(secret, a_encode));
    }

}

} //namespace vault

#endif // VAULT_SECRETS_HXX