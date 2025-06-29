#include "JniOwner.hpp"

JniOwner::JniOwner(const ares::ClassFile &jni_class, std::vector <const ares::MethodInfo *> jni_methods) 
        : jni_class(jni_class), jni_methods(jni_methods) {

}

JniOwner::~JniOwner() {
}
