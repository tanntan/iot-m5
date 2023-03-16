pipeline {
  agent any
  stages {
    stage('script run') {
      steps {
        sh 'apt-get update'
      }
    }

    stage('install python3') {
      parallel {
        stage('install python3') {
          steps {
            sh 'apt-get install python3'
          }
        }

        stage('pip3 install') {
          steps {
            sh 'apt-get install python3-pip'
          }
        }

      }
    }

    stage('install pyelftools') {
      parallel {
        stage('install pyelftools') {
          steps {
            sh 'pip3 install pyelftools'
          }
        }

        stage('install platformio') {
          steps {
            sh 'pip3 install platformio'
          }
        }

      }
    }

  }
}