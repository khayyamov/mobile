// Copyright 2016 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef __wireguardwarp_seq_ANDROID_HDR__
#define __wireguardwarp_seq_ANDROID_HDR__

#include <stdint.h>
#include <android/log.h>
// For abort()
#include <stdlib.h>
#include <jni.h>

#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, "wireguardwarp/Seq", __VA_ARGS__)
#define LOG_FATAL(...)                                             \
  {                                                                \
    __android_log_print(ANDROID_LOG_FATAL, "wireguardwarp/Seq", __VA_ARGS__); \
    abort();                                                       \
  }

// Platform specific types
typedef struct nstring {
	// UTF16 or UTF8 Encoded string. When converting from Java string to Go
	// string, UTF16. When converting from Go to Java, UTF8.
	void *chars;
	// length in bytes, regardless of encoding
	jsize len;
} nstring;
typedef struct nbyteslice {
	void *ptr;
	jsize len;
} nbyteslice;
typedef jlong nint;

extern void wireguardwarp_seq_dec_ref(int32_t ref);
extern void wireguardwarp_seq_inc_ref(int32_t ref);
// wireguardwarp_seq_unwrap takes a reference number to a Java wrapper and returns
// a reference number to its wrapped Go object.
extern int32_t wireguardwarp_seq_unwrap(jint refnum);
extern int32_t wireguardwarp_seq_to_refnum(JNIEnv *env, jobject o);
extern int32_t wireguardwarp_seq_to_refnum_go(JNIEnv *env, jobject o);
extern jobject wireguardwarp_seq_from_refnum(JNIEnv *env, int32_t refnum, jclass proxy_class, jmethodID proxy_cons);

extern void wireguardwarp_seq_maybe_throw_exception(JNIEnv *env, jobject msg);
// wireguardwarp_seq_get_exception returns any pending exception and clears the exception status.
extern jobject wireguardwarp_seq_get_exception(JNIEnv *env);

extern jbyteArray wireguardwarp_seq_to_java_bytearray(JNIEnv *env, nbyteslice s, int copy);
extern nbyteslice wireguardwarp_seq_from_java_bytearray(JNIEnv *env, jbyteArray s, int copy);
extern void wireguardwarp_seq_release_byte_array(JNIEnv *env, jbyteArray arr, jbyte* ptr);

extern jstring wireguardwarp_seq_to_java_string(JNIEnv *env, nstring str);
extern nstring wireguardwarp_seq_from_java_string(JNIEnv *env, jstring s);

// push_local_frame retrieves or creates the JNIEnv* for the current thread
// and pushes a JNI reference frame. Must be matched with call to pop_local_frame.
extern JNIEnv *wireguardwarp_seq_push_local_frame(jint cap);
// Pop the current local frame, releasing all JNI local references in it
extern void wireguardwarp_seq_pop_local_frame(JNIEnv *env);

// Return a global reference to the given class. Return NULL and clear exception if not found.
extern jclass wireguardwarp_seq_find_class(const char *name);
extern jmethodID wireguardwarp_seq_get_static_method_id(jclass clazz, const char *name, const char *sig);
extern jmethodID wireguardwarp_seq_get_method_id(jclass clazz, const char *name, const char *sig);
extern int wireguardwarp_seq_isinstanceof(jint refnum, jclass clazz);

#endif // __wireguardwarp_seq_ANDROID_HDR__
