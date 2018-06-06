from mininet.topo import Topo

class MyTopo( Topo ):
    "Simple topology example."

    def __init__( self ):
        "Create custom topo."

        # Initialize topology
        Topo.__init__( self )

        # Add hosts
        Host1 = self.addHost( 'h1' )
        Host2 = self.addHost( 'h2' )
        Host3 = self.addHost( 'h3' )
        Host4 = self.addHost( 'h4' )
        Host5 = self.addHost( 'h5' )
        Host6 = self.addHost( 'h6' )
        Host7 = self.addHost( 'h7' )
        Host8 = self.addHost( 'h8' )
        # Add switches
	Switch1 = self.addSwitch( 's1' )
        Switch2 = self.addSwitch( 's2' )
        Switch3 = self.addSwitch( 's3' )
        Switch4 = self.addSwitch( 's4' )
        Switch5 = self.addSwitch( 's5' )
        Switch6 = self.addSwitch( 's6' )
        Switch7 = self.addSwitch( 's7' )
        # Add links
        self.addLink( Host1, Switch4 )
        self.addLink( Host2, Switch4 )
        self.addLink( Host3, Switch5 )
        self.addLink( Host4, Switch5 )
        self.addLink( Host5, Switch6 )
        self.addLink( Host6, Switch6 )
        self.addLink( Host7, Switch7 )
        self.addLink( Host8, Switch7 )
        self.addLink( Switch4, Switch2 )
        self.addLink( Switch5, Switch2 )
        self.addLink( Switch6, Switch3 )
        self.addLink( Switch7, Switch3 )
        self.addLink( Switch2, Switch1 )
        self.addLink( Switch3, Switch1 )

topos = { 'mytopo': ( lambda: MyTopo() ) }
