//
//  ContentView.swift
//  BlisSandboxOnA14
//
//  Created by RuQing Xu on 2021/10/16.
//

import SwiftUI

struct ContentView: View {
    @State var message = "This showcase tests Apple AMX2 GEMM performance on you iOS device."
    var body: some View {
        VStack {
            Text(message)
                .padding()
                .font(.system(size: 11, design: .monospaced))
            
            Button(action: runTests) {
                Text("Run")
            }
        }
    }
    func runTests() {
        message = ""
        message = message
            + "******** (   0,    0,    0): " + String(0)                              + " GFlOps/sec\n"
            + "F16<-F16 ( 720,  720,  720): " + String(test_shgemm ( 720,  720,  720)) + " GFlOps/sec\n"
            + "F16<-F16 (1280, 1280, 1280): " + String(test_shgemm (1280, 1280, 1280)) + " GFlOps/sec\n"
            + "F16<-F16 (1920, 1920, 1920): " + String(test_shgemm (1920, 1920, 1920)) + " GFlOps/sec\n"
            + "F16<-F16 (2560, 2560, 2560): " + String(test_shgemm (2560, 2560, 2560)) + " GFlOps/sec\n"
        message = message
            + "******** (   0,    0,    0): " + String(0)                              + " GFlOps/sec\n"
            + "I16<-I16 ( 320,  320,  320): " + String(test_i16gemm( 320,  320,  320)) + " GFlOps/sec\n"
            + "I16<-I16 ( 720,  720,  720): " + String(test_i16gemm( 720,  720,  720)) + " GFlOps/sec\n"
            + "I16<-I16 ( 960,  960,  960): " + String(test_i16gemm( 960,  960,  960)) + " GFlOps/sec\n"
            + "I16<-I16 (1280, 1280, 1280): " + String(test_i16gemm(1280, 1280, 1280)) + " GFlOps/sec\n"
        // message = message
        //     + "******** (   0,    0,    0): " + String(0)                                  + " GFlOps/sec\n"
        //     + "F32<-F16 ( 720,  720,  720): " + String(test_s_shgemm   ( 720,  720,  720)) + " GFlOps/sec\n"
        //     + "F32<-F16 (1280, 1280, 1280): " + String(test_s_shgemm   (1280, 1280, 1280)) + " GFlOps/sec\n"
        //     + "F32<-F16 (1920, 1920, 1920): " + String(test_s_shgemm   (1920, 1920, 1920)) + " GFlOps/sec\n"
        //     + "F32<-F16 (2560, 2560, 2560): " + String(test_s_shgemm   (2560, 2560, 2560)) + " GFlOps/sec\n"
        message = message
            + "******** (   0,    0,    0): " + String(0)                                  + " GFlOps/sec\n"
            + "I32<-I16 ( 320,  320,  320): " + String(test_i32_i16gemm( 320,  320,  320)) + " GFlOps/sec\n"
            + "I32<-I16 ( 720,  720,  720): " + String(test_i32_i16gemm( 720,  720,  720)) + " GFlOps/sec\n"
            + "I32<-I16 ( 960,  960,  960): " + String(test_i32_i16gemm( 960,  960,  960)) + " GFlOps/sec\n"
            + "I32<-I16 (1280, 1280, 1280): " + String(test_i32_i16gemm(1280, 1280, 1280)) + " GFlOps/sec\n"
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
