//
//  Example.swift
//  react-native-grpc
//
//  Created by Asger Nohns on 24/10/2021.
//

import Foundation

@objc(HelloWorld)
class HelloWorld: NSObject {

    @objc(sayHello:)
    static func sayHello() -> String {
        return "Hello World!"
    }
}
